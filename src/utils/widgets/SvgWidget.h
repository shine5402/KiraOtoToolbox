#ifndef SVGWIDGET_H
#define SVGWIDGET_H

#include <QWidget>
#include <QSvgRenderer>

// A widget that renders an SVG resource, maintaining aspect ratio and
// respecting HiDPI. Supports swapping between two resource paths
// (e.g. light/dark variants) based on the current palette.
class SvgWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SvgWidget(QWidget *parent = nullptr);
    explicit SvgWidget(const QString &lightResource, const QString &darkResource, QWidget *parent = nullptr);

    void setResources(const QString &lightResource, const QString &darkResource);
    void setFixedHeight(int height);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int heightForWidth(int width) const override;
    bool hasHeightForWidth() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void changeEvent(QEvent *event) override;

private:
    void updateRenderer();
    bool isDarkMode() const;

    QString m_lightResource;
    QString m_darkResource;
    QSvgRenderer m_renderer;
    int m_fixedHeight = 0;
};

#endif // SVGWIDGET_H
