//
// This class is a part of the Qt private implementation, which I seperate it out for this project.
// Modifications were applied for a more universal use case.
// shine_5402
//

/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWidgets module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <kira/widgets/qballontip.h>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QScreen>
#include <QTextLayout>
#include <QTextStream>
#include <QPainter>
#include <QStyle>
#include <QPainterPath>
#include <QBitmap>

//////////////////////////////////////////////////////////////////////
QBalloonTip* QBalloonTip::showBalloon(const QIcon &icon, const QString &title,
                              const QString &message, QWidget *target,
                              QPoint pos, int timeout, bool showArrow)
{
    if (message.isEmpty() && title.isEmpty())
        return nullptr;

    if (pos.isNull())
    {
        pos= target->mapToGlobal(QPoint{target->width() / 2,
                                        target->height() / 2});
    }

    auto balloonTip = new QBalloonTip(icon, title, message, target);
    if (timeout < 0)
        timeout = 10000; //10 s default
    balloonTip->balloon(pos, timeout, showArrow);
    return balloonTip;
}

QBalloonTip::QBalloonTip(const QIcon &icon, const QString &title,
                         const QString &message, QWidget *target)
    : QWidget(target, Qt::ToolTip),
      target(target),
      timerId(-1),
      showArrow(true)
{
    setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(target, SIGNAL(destroyed()), this, SLOT(close()));

#if QT_CONFIG(label)
    QLabel *titleLabel = new QLabel;
    titleLabel->installEventFilter(this);
    titleLabel->setText(title);
    QFont f = titleLabel->font();
    f.setBold(true);
    titleLabel->setFont(f);
    titleLabel->setTextFormat(Qt::PlainText); // to maintain compat with windows
#endif

    const int iconSize = 18;
    const int closeButtonSize = 15;

#if QT_CONFIG(pushbutton)
    QPushButton *closeButton = new QPushButton;
    closeButton->setFlat(true);
    closeButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    closeButton->setIconSize(QSize(closeButtonSize, closeButtonSize));
    closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    closeButton->setFixedSize(closeButtonSize, closeButtonSize);
    QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
#else
    Q_UNUSED(closeButtonSize);
#endif

#if QT_CONFIG(label)
    QLabel *msgLabel = new QLabel;
    msgLabel->installEventFilter(this);
    msgLabel->setText(message);
    msgLabel->setTextFormat(Qt::PlainText);
    msgLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // smart size for the message label
    int limit = msgLabel->screen()->availableGeometry().size().width() / 3;
    if (msgLabel->sizeHint().width() > limit) {
        msgLabel->setWordWrap(true);
        if (msgLabel->sizeHint().width() > limit) {
            /* msgLabel->d_func()->ensureTextControl();
            if (QWidgetTextControl *control = msgLabel->d_func()->control) {
                QTextOption opt = control->document()->defaultTextOption();
                opt.setWrapMode(QTextOption::WrapAnywhere);
                control->document()->setDefaultTextOption(opt);
            } */
            // The Qt team uses QLabel's private implementation part above to make QLabel's wrap behaviour into QTextOption::WrapAnywhere,
            // when horizonal space is not enough. It's weird why standard QLabel does not provide API to change its wrap behaviour though.
            // Since we can not use this trick here, there is a workaround below.
            // Basicly we are layout the text in our own with the help of QTextLayout.
            QTextLayout textLayout;
            textLayout.setText(message);
            auto opt = textLayout.textOption();
            opt.setWrapMode(QTextOption::WrapAnywhere);
            textLayout.setTextOption(opt);
            textLayout.setFont(msgLabel->font());
            int lineWidth = limit;
            textLayout.setCacheEnabled(true);

            textLayout.beginLayout();
            while (true) {
                QTextLine line = textLayout.createLine();
                if (!line.isValid())
                    break;

                line.setLineWidth(lineWidth);
            }
            textLayout.endLayout();

            QString wrappedMsg;
            QTextStream stream(&wrappedMsg);

            for (int i = 0; i < textLayout.lineCount(); ++i){
                auto currentLine = textLayout.lineAt(i);
                stream << textLayout.text().mid(currentLine.textStart(), currentLine.textLength()) << Qt::endl;
            }

            msgLabel->setText(wrappedMsg);
        }
        // Here we allow the text being much smaller than the balloon widget
        // to emulate the weird standard windows behavior.
        msgLabel->setFixedSize(limit, msgLabel->heightForWidth(limit));
    }
#endif

    QGridLayout *layout = new QGridLayout;
#if QT_CONFIG(label)
    if (!icon.isNull()) {
        QLabel *iconLabel = new QLabel;
        iconLabel->setPixmap(icon.pixmap(iconSize, iconSize));
        iconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        iconLabel->setMargin(2);
        layout->addWidget(iconLabel, 0, 0);
        layout->addWidget(titleLabel, 0, 1);
    } else {
        layout->addWidget(titleLabel, 0, 0, 1, 2);
    }
#endif

#if QT_CONFIG(pushbutton)
    layout->addWidget(closeButton, 0, 2);
#endif

#if QT_CONFIG(label)
    layout->addWidget(msgLabel, 1, 0, 1, 3);
#endif
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setContentsMargins(3, 3, 3, 3);
    setLayout(layout);

//    QPalette pal = palette();
//    pal.setColor(QPalette::Window, QColor(0xff, 0xff, 0xe1));
//    pal.setColor(QPalette::WindowText, Qt::black);
//    setPalette(pal);
}

QBalloonTip::~QBalloonTip()
{

}

void QBalloonTip::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), pixmap);
}

void QBalloonTip::resizeEvent(QResizeEvent *ev)
{
    QWidget::resizeEvent(ev);
}

void QBalloonTip::balloon(const QPoint& pos, int msecs, bool showArrow)
{
    this->showArrow = showArrow;
    QRect scr = target->screen()->geometry();
    QSize sizeHint_ = sizeHint();
    const int border = 1;
    const int arrowHeight = 18, arrowOffset = 18, arrowWidth = 18, roundCorner = 7;
    bool arrowAtTop = (pos.y() + sizeHint_.height() + arrowHeight < scr.height());
    bool arrowAtLeft = (pos.x() + sizeHint_.width() - arrowOffset < scr.width());
    constexpr auto margin = 8;
    setContentsMargins(border + margin,  border + (arrowAtTop ? arrowHeight : 0) + margin, border + margin, border + (arrowAtTop ? 0 : arrowHeight) + margin);
    updateGeometry();
    sizeHint_ = sizeHint();

    int ml, mr, mt, mb;
    QSize sz = sizeHint();
    if (!arrowAtTop) {
        ml = mt = 0;
        mr = sz.width() - 1;
        mb = sz.height() - arrowHeight - 1;
    } else {
        ml = 0;
        mt = arrowHeight;
        mr = sz.width() - 1;
        mb = sz.height() - 1;
    }

    QPainterPath path;
    path.moveTo(ml + roundCorner, mt);
    if (arrowAtTop && arrowAtLeft) {
        if (showArrow) {
            path.lineTo(ml + arrowOffset, mt);
            path.lineTo(ml + arrowOffset, mt - arrowHeight);
            path.lineTo(ml + arrowOffset + arrowWidth, mt);
        }
        move(qMax(pos.x() - arrowOffset, scr.left() + 2), pos.y());
    } else if (arrowAtTop && !arrowAtLeft) {
        if (showArrow) {
            path.lineTo(mr - arrowOffset - arrowWidth, mt);
            path.lineTo(mr - arrowOffset, mt - arrowHeight);
            path.lineTo(mr - arrowOffset, mt);
        }
        move(qMin(pos.x() - sizeHint_.width() + arrowOffset, scr.right() - sizeHint_.width() - 2), pos.y());
    }
    path.lineTo(mr - roundCorner, mt);
    path.arcTo(QRect(mr - roundCorner*2, mt, roundCorner*2, roundCorner*2), 90, -90);
    path.lineTo(mr, mb - roundCorner);
    path.arcTo(QRect(mr - roundCorner*2, mb - roundCorner*2, roundCorner*2, roundCorner*2), 0, -90);
    if (!arrowAtTop && !arrowAtLeft) {
        if (showArrow) {
            path.lineTo(mr - arrowOffset, mb);
            path.lineTo(mr - arrowOffset, mb + arrowHeight);
            path.lineTo(mr - arrowOffset - arrowWidth, mb);
        }
        move(qMin(pos.x() - sizeHint_.width() + arrowOffset, scr.right() - sizeHint_.width() - 2),
             pos.y() - sizeHint_.height());
    } else if (!arrowAtTop && arrowAtLeft) {
        if (showArrow) {
            path.lineTo(arrowOffset + arrowWidth, mb);
            path.lineTo(arrowOffset, mb + arrowHeight);
            path.lineTo(arrowOffset, mb);
        }
        move(qMax(pos.x() - arrowOffset, scr.x() + 2), pos.y() - sizeHint_.height());
    }
    path.lineTo(ml + roundCorner, mb);
    path.arcTo(QRect(ml, mb - roundCorner*2, roundCorner*2, roundCorner*2), -90, -90);
    path.lineTo(ml, mt + roundCorner);
    path.arcTo(QRect(ml, mt, roundCorner*2, roundCorner*2), 180, -90);

    // Set the mask
    QBitmap bitmap = QBitmap(sizeHint());
    bitmap.fill(Qt::color0);
    QPainter painter1(&bitmap);
    painter1.setPen(QPen(Qt::color1, border));
    painter1.setBrush(QBrush(Qt::color1));
    painter1.drawPath(path);
    setMask(bitmap);

    // Draw the border
    pixmap = QPixmap(sz);
    QPainter painter2(&pixmap);
    painter2.setPen(QPen(palette().color(QPalette::Base).darker(160), border));
    painter2.setBrush(palette().color(QPalette::Base));
    painter2.drawPath(path);

    if (msecs > 0)
        timerId = startTimer(msecs);
    show();
}

void QBalloonTip::mousePressEvent(QMouseEvent *e)
{
    close();
    if(e->button() == Qt::LeftButton)
        emit messageClicked();
}

void QBalloonTip::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == timerId) {
        killTimer(timerId);
        if (!underMouse())
            close();
        return;
    }
    QWidget::timerEvent(e);
}
