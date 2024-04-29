#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>
#include <iostream>

// fontconfig includes
#include <fontconfig/fontconfig.h>

class FontKonfig : public QMainWindow
{
    Q_OBJECT

public:
    FontKonfig(QWidget *parent = nullptr) : QMainWindow(parent), ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        connect(ui->pushButton, &QPushButton::clicked, this, &FontKonfig::updateTable);
        model = new QStandardItemModel(this);
        ui->tableView->setModel(model);
    }

    virtual ~FontKonfig()
    {
        delete ui;
    }

private slots:
    void updateTable() {
        QString searchString = ui->plainTextEdit->toPlainText();
        //std::cout << "Search string: " << searchString.toStdString() << std::endl;

        // clear table
        model->clear();

        FcConfig *config = FcInitLoadConfigAndFonts();
        FcConfigBuildFonts(config);
        FcPattern *pattern = FcNameParse(reinterpret_cast<const FcChar8*>(searchString.toStdString().c_str()));
        FcObjectSet *os = FcObjectSetBuild(FC_FAMILY, FC_STYLE, FC_FILE, (char *) 0);
        FcFontSet *fs = FcFontList(config, pattern, os);

        if (!fs || fs->nfont == 0) {
            std::cerr << "No fonts found" << std::endl;
            QString title = QString("FontKonfig — No fonts found");
            setWindowTitle(title);
            return;
        }

        int nfont = fs->nfont;
        QString title = QString("FontKonfig — %1 fonts found").arg(nfont);
        setWindowTitle(title);

        for (int i = 0; i < fs->nfont; i++) {
            FcPattern *font = fs->fonts[i];
            FcChar8 *file, *family, *style;
            if (FcPatternGetString(font, FC_FILE, 0, &file) == FcResultMatch) {
                QString familyStr, fileStr, styleStr;
                if (FcPatternGetString(font, FC_FAMILY, 0, &family) == FcResultMatch) {
                    familyStr = QString::fromUtf8(reinterpret_cast<const char*>(family));
                }
                if (FcPatternGetString(font, FC_STYLE, 0, &style) == FcResultMatch) {
                    styleStr = QString::fromUtf8(reinterpret_cast<const char*>(style));
                }
                fileStr = QString::fromUtf8(reinterpret_cast<const char*>(file));
                QList<QStandardItem*> row;
                row.append(new QStandardItem(fileStr));
                row.append(new QStandardItem(familyStr));
                row.append(new QStandardItem(styleStr));
                model->appendRow(row);
            }
        }
        FcPatternDestroy(pattern);
        FcObjectSetDestroy(os);

        // set table width
        ui->tableView->resizeColumnsToContents();
    }

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
};

