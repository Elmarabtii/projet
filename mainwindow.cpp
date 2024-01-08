#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>  // Add this line to include the header for QSqlError
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

// Constructeur de la fenêtre principale
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    performAdminLogin();



    // Connecter le clic du bouton à une fonction
    connect(ui->ajouter_p, SIGNAL(clicked()), this, SLOT(on_ajouter_produit_clicked()));
    connect(ui->b_ajouter, SIGNAL(clicked()), this, SLOT(on_ajouter_client_clicked()));
    connect(ui->b_clients, SIGNAL(clicked()), this, SLOT(on_go_client_clicked()));
    connect(ui->b_fournisseurs, SIGNAL(clicked()), this, SLOT(on_go_fournisseur_clicked()));
    connect(ui->ajouter_f, SIGNAL(clicked()), this, SLOT(on_ajouter_fournisseur_clicked()));
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(on_go_acceuil_clicked()));

     connect(ui->pushButton_20, SIGNAL(clicked()), this, SLOT(on_go_acceuil_clicked()));

     connect(ui->pushButton_23, SIGNAL(clicked()), this, SLOT(on_go_acceuil_clicked()));
     connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(on_go_acceuil_clicked()));
     connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(on_go_acceuil_clicked()));
     connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(on_go_acceuil_clicked()));
     connect(ui->pushButton_23, SIGNAL(clicked()), this, SLOT(on_go_acceuil_clicked()));

     connect(ui->b_produits, SIGNAL(clicked()), this, SLOT(on_go_produits_clicked()));
     connect(ui->b_ventes, SIGNAL(clicked()), this, SLOT(on_go_ventes_clicked()));
     connect(ui->b_stock, SIGNAL(clicked()), this, SLOT(on_go_stock_clicked()));
     connect(ui->ret_acc, SIGNAL(clicked()), this, SLOT(on_go_acc_clicked()));
     connect(ui->liste_fournisseurs, SIGNAL(clicked()), this, SLOT(displayFournisseurs()));
     connect(ui->liste_produits, SIGNAL(clicked()), this, SLOT(displayProduits()));
     connect(ui->ret_acc_2, SIGNAL(clicked()), this, SLOT(on_go_acc2_clicked()));
     connect(ui->ret_acc_3, SIGNAL(clicked()), this, SLOT(on_go_acc3_clicked()));
     connect(ui->liste_clients, SIGNAL(clicked()), this, SLOT(displayClients()));
     connect(ui->b_vente, SIGNAL(clicked()), this, SLOT(on_ajouter_vente_clicked()));
     connect(ui->b_showStock, SIGNAL(clicked()), this, SLOT(on_go_ajs_clicked()));

     connect(ui->b_ajouter_2, SIGNAL(clicked()), this, SLOT(on_ajouter_stock_clicked()));
     connect(ui->ac_achat, SIGNAL(clicked()), this, SLOT(on_go_acc4_clicked()));
     connect(ui->ret_acc_4, SIGNAL(clicked()), this, SLOT(on_go_acc5_clicked()));
     connect(ui->b_ajouter_3, SIGNAL(clicked()), this, SLOT(displayStock()));
     connect(ui->supprimer_clients, SIGNAL(clicked()), this, SLOT(on_supprimer_client_clicked()));
     connect(ui->supprimer_produits, SIGNAL(clicked()), this, SLOT(on_supprimer_produit_clicked()));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

     db.setDatabaseName("C:/Users/DELL/Documents/3IIR need S5/Cplusplus/gestion_stock/bdqt/db.db");
    if (!db.open()) {
        qDebug() << "Erreur lors de l'ouverture de la base de données :" << db.lastError().text();
        // Gérer l'erreur d'ouverture de la base de données
    } else {
        qDebug() << "Connexion à la base de données établie avec succès.";
        // Réalisez les opérations sur la base de données (ajout de tables, etc.) si nécessaire
    }
}

// Fonction appelée lorsque le bouton est cliqué
void MainWindow::on_ajouter_produit_clicked()
{
    QString nom = ui->i_nom->text();
    int prix = ui->i_prix->text().toInt();


    qDebug() << "Nom:" << nom << ", Prix:" << prix ;

    // Exécution de la requête SQL pour l'ajout dans la table 'produits'
    QSqlQuery query;
    query.prepare("INSERT INTO produits (nom, prix) VALUES (:Nom, :Prix)");
    query.bindValue(":Nom", nom);
    query.bindValue(":Prix", prix);


    if (query.exec()) {
        qDebug() << "Produit ajouté avec succès.";
        // Effectuer d'autres actions suite à l'ajout
    } else {
        qDebug() << "Erreur lors de l'ajout d'un produit :" << query.lastError().text();
        // Gérer l'erreur d'ajout
    }
}


void MainWindow::on_ajouter_vente_clicked()
{
    QString i_Client = ui->i_client->text();
    int i_produit = ui->i_produit_2->text().toInt();
    int i_quantite_2 = ui->i_quantite_2->text().toInt();
    float i_paye = ui->i_paye->text().toFloat();  // Assuming Paye is a FLOAT in the database

    QSqlQuery query;
    query.prepare("INSERT INTO ventes (idClient, idProduit, quantite, Paye) VALUES (:i_Client, :i_produit, :i_quantite_2, :i_paye)");
    query.bindValue(":i_Client", i_Client);
    query.bindValue(":i_produit", i_produit);
    query.bindValue(":i_quantite_2", i_quantite_2);
    query.bindValue(":i_paye", i_paye);

    if (query.exec()) {
        qDebug() << "Vente ajoutée avec succès.";
        // Effectuer d'autres actions suite à l'ajout
    } else {
        qDebug() << "Erreur lors de l'ajout d'une vente:" << query.lastError().text();
        // Gérer l'erreur d'ajout
    }
}



void MainWindow::on_ajouter_stock_clicked()
{
    int i_quantite = ui->i_quantite->text().toInt();
    int i_produit_stock = ui->i_produit_stock->text().toInt();


    QSqlQuery query;
    query.prepare("INSERT INTO stock (idProduit,quantite) VALUES (:i_produit_stock, :i_quantite)");
    query.bindValue(":i_produit_stock", i_produit_stock);
    query.bindValue(":i_quantite", i_quantite);


    if (query.exec()) {
        qDebug() << "produit  ajoutée au stock avec succès.";
        // Effectuer d'autres actions suite à l'ajout
    } else {
        qDebug() << "Erreur lors de l'ajout d'un produit au stock:" << query.lastError().text();
        // Gérer l'erreur d'ajout
    }
}

void MainWindow::on_ajouter_client_clicked()
{
    QString nom = ui->i_nom_2->text();
    QString prenom = ui->i_prenom->text();
    QString tel = ui->i_tel->text();


    // Exécution de la requête SQL pour l'ajout dans la table 'clients'
    QSqlQuery query;
    query.prepare("INSERT INTO clients (nom, prenom,tel) VALUES (:Nom, :prenom,:tel)");
    query.bindValue(":Nom", nom);
    query.bindValue(":prenom", prenom);
     query.bindValue(":tel", tel);

    if (query.exec()) {
        qDebug() << "client ajouté avec succès.";
        // Effectuer d'autres actions suite à l'ajout
    } else {
        qDebug() << "Erreur lors de l'ajout d'un client :" << query.lastError().text();
        // Gérer l'erreur d'ajout
    }
}


void MainWindow::on_ajouter_fournisseur_clicked()
{
    QString nom = ui->nom_f->text();
    QString prenom = ui->prenom_f->text();
    QString tel = ui->tel_f->text();
    QString adresse = ui->adresse_f->text();



    // ExÃ©cution de la requÃªte SQL pour l'ajout dans la table 'fournisseurs'
    QSqlQuery query;
    query.prepare("INSERT INTO fournisseurs (nom, prenom, telephone, adresse) VALUES (:Nom, :Prenom, :Tel, :Adresse)");
    query.bindValue(":Nom", nom);
    query.bindValue(":Prenom", prenom);
    query.bindValue(":Tel", tel);
    query.bindValue(":Adresse", adresse);



    if (query.exec()) {
        qDebug() << "Fournisseur ajouté avec succées.";
        // Effectuer d'autres actions suite Ã  l'ajout
     } else {
        qDebug() << "Erreur lors de l'ajout d'un fournisseur:" << query.lastError().text();
        // Gérer l'erreur d'ajout
    }


}

void MainWindow::on_go_acceuil_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_go_acc2_clicked(){
     ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_go_acc3_clicked(){
    ui->stackedWidget->setCurrentIndex(0);


}

void MainWindow::on_go_acc4_clicked(){
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_go_ajs_clicked(){
    ui->stackedWidget->setCurrentIndex(10);

}
void MainWindow::on_go_acc5_clicked(){
    ui->stackedWidget->setCurrentIndex(0);

}

    void MainWindow::on_go_client_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_go_stock_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_go_fournisseur_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow ::on_go_produits_clicked(){
     ui->stackedWidget->setCurrentIndex(9);
}
void MainWindow ::on_go_ventes_clicked(){
     ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow ::on_go_acc_clicked(){
      ui->stackedWidget->setCurrentIndex(0);
}
bool MainWindow::performAdminLogin()
{
    bool ok;
    QString username = QInputDialog::getText(this, "Login", "Enter username:", QLineEdit::Normal, "", &ok);

    if (ok && !username.isEmpty()) {
        QString password = QInputDialog::getText(this, "Login", "Enter password:", QLineEdit::Password, "", &ok);

        if (ok && !password.isEmpty()) {
            // Check if the entered username and password are correct
            if (isValidAdminCredentials(username, password)) {
                ui->stackedWidget->setCurrentIndex(0);
                // Admin login successful
                return true;
            } else {
                // Invalid credentials, show an error message and retry
                QMessageBox::critical(this, "Login Failed", "Invalid username or password. Please try again.");
                return performAdminLogin(); // Recursive call to retry login
            }
        } else {
            // User canceled password input, close the application
            QApplication::quit();
            return false;
        }
    } else {
        // User canceled username input, close the application
        QApplication::quit();
        return false;
    }
}

bool MainWindow::isValidAdminCredentials(const QString &username, const QString &password)
{
    // Replace this function with your logic to validate admin credentials
    // For example, you might compare against a predefined admin username and password
    return (username == "admin" && password == "admin123");
}

void MainWindow::displayFournisseurs() {
    ui->stackedWidget->setCurrentIndex(4);  // Switch to the QueryDialog1 page

    if (!ui || !ui->fournisseursTable) {
        qDebug() << "UI elements not initialized properly.";
        return;
    }

    // Find fournisseursTable on QueryDialog1 page
    QWidget* queryDialog1Page = ui->stackedWidget->currentWidget();
    QTableWidget* fournisseursTable = queryDialog1Page->findChild<QTableWidget*>("fournisseursTable");

    if (!fournisseursTable) {
        qDebug() << "fournisseursTable not found on QueryDialog1 page.";
        return;
    }


        // Clear the existing items in the table
        fournisseursTable->clearContents();

        // Set the headers for the table
        fournisseursTable->setRowCount(0);  // Clear all rows
        fournisseursTable->setColumnCount(5);  // Assuming there are 5 columns in the "Fournisseurs" table
        fournisseursTable->setHorizontalHeaderLabels(QStringList() << "ID" << "Nom" << "Prenom" << "Adresse" << "Telephone");

        // SQL query to retrieve fournisseurs
        QSqlQuery query("SELECT * FROM Fournisseurs");

        // Populate the table with the query results
        int row = 0;
        while (query.next()) {
            int id = query.value("id").toInt();
            QString nom = query.value("nom").toString();
            QString prenom = query.value("prenom").toString();
            QString adresse = query.value("adresse").toString();
            int telephone = query.value("telephone").toInt();

            // If the row is out of bounds, insert a new row
            if (row >= fournisseursTable->rowCount()) {
                fournisseursTable->insertRow(row);
            }

            // Set data in the table
            fournisseursTable->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
            fournisseursTable->setItem(row, 1, new QTableWidgetItem(nom));
            fournisseursTable->setItem(row, 2, new QTableWidgetItem(prenom));
            fournisseursTable->setItem(row, 3, new QTableWidgetItem(adresse));
            fournisseursTable->setItem(row, 4, new QTableWidgetItem(QString::number(telephone)));

            row++;
        }

        // Automatically resize columns to fit content
        for (int i = 0; i < fournisseursTable->columnCount(); ++i) {
            fournisseursTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
        }


}

void MainWindow::displayProduits() {
    ui->stackedWidget->setCurrentIndex(5);  // Switch to the QueryDialog2 page

    if (!ui || !ui->produitsTable) {
        qDebug() << "UI elements not initialized properly.";
        return;
    }

    // Find produitsTable on QueryDialog2 page
    QWidget* queryDialog2Page = ui->stackedWidget->currentWidget();
    QTableWidget* produitsTable = queryDialog2Page->findChild<QTableWidget*>("produitsTable");

    if (!produitsTable) {
        qDebug() << "produitsTable not found on QueryDialog2 page.";
        return;
    }


    // Clear the existing items in the table
    produitsTable->clearContents();

    // Set the headers for the table
    produitsTable->setRowCount(0);  // Clear all rows
    produitsTable->setColumnCount(4);
    produitsTable->setHorizontalHeaderLabels(QStringList() << "ID" << "Nom" << "Prix" << "ID_f" );

    // SQL query to retrieve produits
    QSqlQuery query("SELECT * FROM produits");

    // Populate the table with the query results
    int row = 0;
    while (query.next()) {
        int id = query.value("id").toInt();
        QString nom = query.value("nom").toString();
        float prix = query.value("prix").toFloat();
        int id_f = query.value("id_f").toInt();

        // If the row is out of bounds, insert a new row
        if (row >= produitsTable->rowCount()) {
            produitsTable->insertRow(row);
        }

        // Set data in the table
        produitsTable->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
        produitsTable->setItem(row, 1, new QTableWidgetItem(nom));
        produitsTable->setItem(row, 2, new QTableWidgetItem(QString::number(prix)));
        produitsTable->setItem(row, 3, new QTableWidgetItem(QString::number(id_f)));

        row++;
    }

    // Automatically resize columns to fit content
    for (int i = 0; i < produitsTable->columnCount(); ++i) {
        produitsTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }


}


void MainWindow::displayClients() {
    ui->stackedWidget->setCurrentIndex(6);

    if (!ui || !ui->clientsTable) {
        qDebug() << "UI elements not initialized properly.";
        return;
    }

    // Find clientsTable on QueryDialog3 page
    QWidget* queryDialog3Page = ui->stackedWidget->currentWidget();
    QTableWidget* clientsTable = queryDialog3Page->findChild<QTableWidget*>("clientsTable");

    if (!clientsTable) {
        qDebug() << "clientsTable not found on QueryDialog3 page.";
        return;
    }


    // Clear the existing items in the table
    clientsTable->clearContents();

    // Set the headers for the table
    clientsTable->setRowCount(0);  // Clear all rows
    clientsTable->setColumnCount(4);
    clientsTable->setHorizontalHeaderLabels(QStringList() << "ID" << "Nom" << "Prenom"  << "Telephone");

    // SQL query to retrieve fournisseurs
    QSqlQuery query("SELECT * FROM Clients");

    // Populate the table with the query results
    int row = 0;
    while (query.next()) {
        int id = query.value("id").toInt();
        QString nom = query.value("nom").toString();
        QString prenom = query.value("prenom").toString();
        int tel = query.value("tel").toInt();

        // If the row is out of bounds, insert a new row
        if (row >= clientsTable->rowCount()) {
            clientsTable->insertRow(row);
        }

        // Set data in the table
       clientsTable->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
       clientsTable->setItem(row, 1, new QTableWidgetItem(nom));
       clientsTable->setItem(row, 2, new QTableWidgetItem(prenom));
       clientsTable->setItem(row, 3, new QTableWidgetItem(QString::number(tel)));

        row++;
    }

    // Automatically resize columns to fit content
    for (int i = 0; i <clientsTable->columnCount(); ++i) {
       clientsTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }


}



void MainWindow::displayStock() {
    ui->stackedWidget->setCurrentIndex(2);

    if (!ui || !ui->stockTable) {
        qDebug() << "UI elements not initialized properly.";
        return;
    }


    QWidget* queryDialog4Page = ui->stackedWidget->currentWidget();
    QTableWidget* stockTable = queryDialog4Page->findChild<QTableWidget*>("stockTable");

    if (!stockTable) {
        qDebug() << "stockTable not found on QueryDialog4 page.";
        return;
    }



    stockTable->clearContents();


    stockTable->setRowCount(0);  // Clear all rows
    stockTable->setColumnCount(3);
    stockTable->setHorizontalHeaderLabels(QStringList() << "ID" << "IDProduit" << "Quantite");


    QSqlQuery query("SELECT * FROM Stock");


    int row = 0;
    while (query.next()) {
        int id = query.value("id").toInt();
        int id_Produit = query.value("id_Produit").toInt();
        int quantite = query.value("quantite").toInt();


        if (row >= stockTable->rowCount()) {
            stockTable->insertRow(row);
        }


        stockTable->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
        stockTable->setItem(row, 1, new QTableWidgetItem(QString::number(id_Produit)));
        stockTable->setItem(row, 2, new QTableWidgetItem(QString::number(quantite)));
        row++;
    }


    for (int i = 0; i <stockTable->columnCount(); ++i) {
        stockTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }


}

void MainWindow::on_supprimer_client_clicked()
{
    // Get input values from UI
    QString prenomToDelete = ui->i_prenom->text();
    QString telToDelete = ui->i_tel->text();

    // Execute SQL query to delete the client with the specified first name and phone number
    QSqlQuery query;
    query.prepare("DELETE FROM clients WHERE prenom = :Prenom AND tel = :Tel");
    query.bindValue(":Prenom", prenomToDelete);
    query.bindValue(":Tel", telToDelete);

    if (query.exec()) {
        qDebug() << "Client supprimé avec succès.";
        // Effectuer d'autres actions suite à la suppression
    } else {
        qDebug() << "Erreur lors de la suppression du client :" << query.lastError().text();
        // Gérer l'erreur de suppression
    }
}

void MainWindow::on_supprimer_produit_clicked()
{
    // Get input values from UI
    QString nompToDelete = ui->i_nom->text();
    int prixToDelete = ui->i_prix->text().toInt();

    QSqlQuery query;
    query.prepare("DELETE FROM produits WHERE nom = :Nom AND prix = :Prix");
    query.bindValue(":Nom", nompToDelete);
    query.bindValue(":Prix", prixToDelete);

    if (query.exec()) {
        qDebug() << "Produit supprimé avec succès.";
        // Effectuer d'autres actions suite à la suppression
    } else {
        qDebug() << "Erreur lors de la suppression du produit :" << query.lastError().text();
        // Gérer l'erreur de suppression
    }
}










// Destructeur de la fenêtre principale
MainWindow::~MainWindow()
{
    delete ui;
}
