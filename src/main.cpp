#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QMouseEvent>
#include <poppler-qt6.h>

class PDFReader : public QMainWindow {
    Q_OBJECT

public:
    PDFReader(QWidget* parent = nullptr) : QMainWindow(parent), currentPage(0), isDrawing(false) {
        QWidget* centralWidget = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(centralWidget);

        pdfDoc = Poppler::Document::load("sample.pdf");
        if (!pdfDoc || pdfDoc->isLocked()) {
            QLabel* errorLabel = new QLabel("Failed to load PDF", this);
            layout->addWidget(errorLabel);
        }
        else {
            pdfDoc->setRenderHint(Poppler::Document::TextAntialiasing);
            imageLabel = new QLabel(this);
            layout->addWidget(imageLabel);

            searchBox = new QLineEdit(this);
            QPushButton* searchButton = new QPushButton("Search", this);
            layout->addWidget(searchBox);
            layout->addWidget(searchButton);

            QPushButton* prevButton = new QPushButton("Previous", this);
            QPushButton* nextButton = new QPushButton("Next", this);
            layout->addWidget(prevButton);
            layout->addWidget(nextButton);

            QPushButton* highlightButton = new QPushButton("Highlight", this);
            QPushButton* drawButton = new QPushButton("Draw", this);
            layout->addWidget(highlightButton);
            layout->addWidget(drawButton);

            connect(prevButton, &QPushButton::clicked, this, &PDFReader::prevPage);
            connect(nextButton, &QPushButton::clicked, this, &PDFReader::nextPage);
            connect(searchButton, &QPushButton::clicked, this, &PDFReader::searchText);
            connect(highlightButton, &QPushButton::clicked, this, &PDFReader::highlightText);
            connect(drawButton, &QPushButton::clicked, this, &PDFReader::enableDrawing);

            updatePage();
        }
        setCentralWidget(centralWidget);
    }

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (isDrawing) {
            drawnPoints.append(event->pos());
            updatePage();
        }
    }

private slots:
    void nextPage() {
        if (pdfDoc && currentPage < pdfDoc->numPages() - 1) {
            currentPage++;
            drawnPoints.clear();
            updatePage();
        }
    }

    void prevPage() {
        if (pdfDoc && currentPage > 0) {
            currentPage--;
            drawnPoints.clear();
            updatePage();
        }
    }

    void searchText() {
        if (!pdfDoc) return;
        QString keyword = searchBox->text();
        if (keyword.isEmpty()) return;

        Poppler::Page* page = pdfDoc->page(currentPage);
        if (!page) return;

        QList<Poppler::TextBox*> results = page->textList();
        QImage img = page->renderToImage(2.0 * physicalDpiX(), 2.0 * physicalDpiY());
        QPainter painter(&img);
        painter.setPen(Qt::red);

        for (Poppler::TextBox* box : results) {
            if (box->text().contains(keyword, Qt::CaseInsensitive)) {
                QRectF rect = box->boundingBox();
                painter.fillRect(rect, QColor(255, 255, 0, 100)); // Yellow highlight
            }
        }
        painter.end();
        imageLabel->setPixmap(QPixmap::fromImage(img));
    }

    void highlightText() {
        searchText(); // Reuse search function to highlight found text
    }

    void enableDrawing() {
        isDrawing = !isDrawing;
    }

private:
    void updatePage() {
        if (!pdfDoc) return;
        QImage img = pdfDoc->page(currentPage)->renderToImage(2.0 * physicalDpiX(), 2.0 * physicalDpiY());
        QPainter painter(&img);
        painter.setPen(QPen(Qt::blue, 3));

        for (const QPoint& point : drawnPoints) {
            painter.drawEllipse(point, 5, 5);
        }
        painter.end();
        imageLabel->setPixmap(QPixmap::fromImage(img));
    }

    Poppler::Document* pdfDoc;
    QLabel* imageLabel;
    QLineEdit* searchBox;
    int currentPage;
    bool isDrawing;
    QVector<QPoint> drawnPoints;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    PDFReader reader;
    reader.resize(800, 600);
    reader.show();
    return app.exec();
}
