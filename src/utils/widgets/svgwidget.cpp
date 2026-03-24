#include "svgwidget.h"

#include <QPainter>
#include <QPalette>
#include <QEvent>

SvgWidget::SvgWidget(QWidget *parent)
    : QWidget(parent)
{
}

SvgWidget::SvgWidget(const QString &lightResource, const QString &darkResource, QWidget *parent)
    : QWidget(parent)
    , m_lightResource(lightResource)
    , m_darkResource(darkResource)
{
    updateRenderer();
}

void SvgWidget::setResources(const QString &lightResource, const QString &darkResource)
{
    m_lightResource = lightResource;
    m_darkResource = darkResource;
    updateRenderer();
    updateGeometry();
    update();
}

void SvgWidget::setFixedHeight(int height)
{
    m_fixedHeight = height;
    updateGeometry();
    update();
}

bool SvgWidget::isDarkMode() const
{
    return palette().color(QPalette::Window).lightness() < 128;
}

void SvgWidget::updateRenderer()
{
    const QString &resource = isDarkMode() ? m_darkResource : m_lightResource;
    m_renderer.load(resource);
}

QSize SvgWidget::sizeHint() const
{
    if (!m_renderer.isValid())
        return QSize(0, 0);

    QSizeF svgSize = m_renderer.defaultSize();
    if (m_fixedHeight > 0) {
        qreal aspect = svgSize.width() / svgSize.height();
        return QSize(qRound(m_fixedHeight * aspect), m_fixedHeight);
    }
    return svgSize.toSize();
}

QSize SvgWidget::minimumSizeHint() const
{
    return sizeHint();
}

bool SvgWidget::hasHeightForWidth() const
{
    return m_renderer.isValid();
}

int SvgWidget::heightForWidth(int width) const
{
    if (!m_renderer.isValid())
        return -1;

    QSizeF svgSize = m_renderer.defaultSize();
    return qRound(width * svgSize.height() / svgSize.width());
}

void SvgWidget::paintEvent(QPaintEvent *)
{
    if (!m_renderer.isValid())
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Fit the SVG into the widget rect, keeping aspect ratio, aligned left
    QSizeF svgSize = m_renderer.defaultSize();
    QSizeF targetSize = svgSize.scaled(size(), Qt::KeepAspectRatio);
    QRectF targetRect(QPointF(0, (height() - targetSize.height()) / 2.0), targetSize);

    m_renderer.render(&painter, targetRect);
}

void SvgWidget::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::ApplicationPaletteChange || event->type() == QEvent::PaletteChange) {
        updateRenderer();
        update();
    }
}
