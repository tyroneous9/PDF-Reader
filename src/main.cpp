#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <poppler-qt6.h>

class PDFReader : public QMainWindow {
    Q_OBJECT

public:
    PDFReader(QWidget *parent = nullptr) : QMainWindow(parent), currentPage(0) {
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        pdfDoc = new Poppler::Document("sample.pdf");
        if (!pdfDoc || pdfDoc->isLocked()) {
            QLabel *errorLabel = new QLabel("Failed to load PDF", this);
            layout->addWidget(errorLabel);
        } else {
            pdfDoc->setRenderHint(Poppler::Document::TextAntialiasing);
            imageLabel = new QLabel(this);
            layout->addWidget(imageLabel);
            updatePage();

            QPushButton *prevButton = new QPushButton("Previous", this);
            QPushButton *nextButton = new QPushButton("Next", this);
            layout->addWidget(prevButton);
            layout->addWidget(nextButton);

            connect(prevButton, &QPushButton::clicked, this, &PDFReader::prevPage);
            connect(nextButton, &QPushButton::clicked, this, &PDFReader::nextPage);
        }

        setCentralWidget(centralWidget);
    }

private slots:
    void nextPage() {
        if (pdfDoc && currentPage < pdfDoc->numPages() - 1) {
            currentPage++;
            updatePage();
        }
    }

    void prevPage() {
        if (pdfDoc && currentPage > 0) {
            currentPage--;
            updatePage();
        }
    }

private:
    void updatePage() {
        if (!pdfDoc) return;
        QImage img = pdfDoc->page(currentPage)->renderToImage(2.0 * physicalDpiX(), 2.0 * physicalDpiY());
        imageLabel->setPixmap(QPixmap::fromImage(img));
    }

    Poppler::Document *pdfDoc;
    QLabel *imageLabel;
    int currentPage;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PDFReader reader;
    reader.resize(800, 600);
    reader.show();
    return app.exec();
}
