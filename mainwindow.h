#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"

// Déclaration de la classe MainWindow
namespace Ui {
class MainWindow;
}

// Définition de la classe MainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getLastDateModified();
    void setLastDateModified();
    Database *getDatabase();

public slots:
    void on_ajouter_produit_clicked();
    void on_ajouter_client_clicked();
    void on_go_client_clicked();
    void on_go_fournisseur_clicked();
    void on_ajouter_fournisseur_clicked();
    void on_go_acceuil_clicked();
    void on_go_produits_clicked();
    void on_go_ventes_clicked();
    void on_go_acc_clicked();
    void on_go_stock_clicked();
    void displayFournisseurs();
    void displayProduits();
    void on_go_acc2_clicked();
    void on_go_acc3_clicked();
    void displayClients();

    void on_ajouter_vente_clicked();
    void on_go_ajs_clicked();

    void on_ajouter_stock_clicked();
    void on_go_acc4_clicked();
    void displayStock();
    void on_go_acc5_clicked();
    void on_supprimer_client_clicked();
    void on_supprimer_produit_clicked();
private:
    Ui::MainWindow *ui;
    Database *m_db;
    bool performAdminLogin();
    bool isValidAdminCredentials(const QString &username, const QString &password);

};

#endif // MAINWINDOW_H
