#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<queue>

using namespace std;

class MHThucPham{
    private:
        string ma;
        string name;
        double price;
    public:
        MHThucPham() {
            this->name = "";
            this->price = 0;
            this->ma = "";
        }
        MHThucPham(string ma, string name, double price) {
            this->ma = ma;
            this->name = name;
            this->price = price;
        }
        string getName() {
            return this->name;
        }
        double getPrice() {
            return this->price;
        }
        string getMa() {
            return this->ma;
        }
        void setName(string n) {
            this->name = n;
        }
        void setMa(string m) {
            this->ma = m;
        }
        void setPrice(double p) {
            this->price = p;
        }
        virtual void print() = 0;
};
class Nuoc : public MHThucPham{
    protected:
        string hsd;
    public: 
        Nuoc(string ma, string name, double price, string hsd) : MHThucPham(ma, name, price) {
            this->hsd = hsd;
        }
        string getHsd() {
            return hsd;
        }
        void print() {
            cout << "\t" << getMa() << " " << getName() << "\t\tGia tien: " << getPrice() << " VND"<< "\tHan su dung:" << this->hsd << endl;
        }
};
class MonAn : public MHThucPham {
    protected: 
        string XuatXu;
    public:
        MonAn(string ma, string name, double price, string XuatXu) : MHThucPham(ma, name, price) {
            this->XuatXu = XuatXu;
        }
        string getXuatXu() {
            return XuatXu;
        }
        void print() {
            cout << "\t" << getMa() << " " << getName() << "\t\tGia tien: " << getPrice() << " VND" << "\tNguon goc:  " << this->XuatXu << endl;
        }
};
class HoaDon {
    private:
        vector<MHThucPham*> dsmonan;
        queue<int> qtyy;
        double tongTien;
        //int qty;
    public:
        HoaDon() {
            this->tongTien = 0;
        }
        void themds(MHThucPham* a, int qty){
            dsmonan.push_back(a);
            tongTien += a->getPrice()*qty;
            //this->qty = qty;
            qtyy.push(qty);
        }
        void print() {
            cout <<"\t\tMA MON" << "\t\t  TEN MON" << "\t\tGIA TIEN" <<"\t\tSO LUONG" <<endl;
            cout <<"\t\t___________________________________________________________________________" <<endl;
            for (MHThucPham* a:dsmonan){
                    cout << "\n\t\t" << a->getMa() << "\t\t" << a->getName() << "\t\t\t" << a->getPrice() << " VND\t\t\t" << qtyy.front() <<endl;
                    qtyy.pop();
                }
            cout << "\n\t\tTong so tien: " << this->tongTien << " VND" << endl;
        }
};
class Menu {
    private: 
        vector<MHThucPham*> menu;
    public:
        Menu() {}
        Menu(string);
        void print();
        void themMon();
        void xoaMon(int);
        void datban();
        void thayDoiID(int i) {
            string ID_td;
            cout << "New ID: ";
            cin >> ID_td;
            menu[i]->setMa(ID_td);
        }
        void thayDoiTen(int i) {
            string ten;
            cin.ignore();
            cout << "New Name: ";
            getline(cin, ten);
            menu[i]->setName(ten);
        }
        void thayDoiGia(int i) {
            double gia;
            cout << "New Price: ";
            cin >> gia;
            menu[i]->setPrice(gia);
        }
        void thayDoi();

        MHThucPham* getMenu(int i) {
            return menu[i];
        }
        int getSize() {
            return menu.size();
        }
        ~Menu() {
            for (MHThucPham* a:menu) delete a;
        }
};


Menu::Menu(string filename){
    ifstream file(filename);
    if (file.is_open()) {
        string dong;
        while (getline(file, dong)) {
            stringstream ss(dong);
            string loai;
            string ten;
            string ma;
            string hsd;
            double gia;
            string xuatxu;
            bool isCarbonated;
            getline(ss, loai, ',');
            getline(ss, ma, ',');
            getline(ss, ten, ',');
            ss >> gia;
            ss.ignore();
            if (loai == "Mon An") {
                getline(ss, xuatxu, ',');
                menu.push_back(new MonAn(ma, ten, gia, xuatxu));
            }
            else if (loai == "Nuoc") {
                getline(ss, hsd, ',');
                menu.push_back(new Nuoc(ma, ten, gia, hsd));
            }
        }
        file.close();
    }
    else cout << "Khong mo duoc file !!!!" << endl;
}

void Menu::print() {
    cout << "\t\t=====================MENU=====================\t\t" << endl;
    cout << "\t_______________________________________________________________________" << endl;
    cout << "\tCAC LOAI NUOC\n"; 
    for (MHThucPham* a:menu) {
        if (dynamic_cast<Nuoc*>(a)) {
            a->print();
        }
    }
    cout << "\t_______________________________________________________________________" << endl;
    cout << "\tCAC MON AN\n";
    for (MHThucPham* a:menu) {
        if (dynamic_cast<MonAn*>(a)) {
            a->print();
        }
    }
}

void Menu::themMon() {
    string loai;
    string ten;
    string ma;
    double gia;
    string hsd;
    string xuatxu;
    cin.ignore();
    cout << "Nhap loai mon an hay nuoc uong: ";
    getline(cin, loai);
    cout << "Nhap ma: ";
    getline(cin, ma);
    cout << "Nhap ten: ";
    getline(cin, ten);
    cout << "Nhap gia: ";
    cin >> gia;
    cin.ignore();
    if (loai == "Mon An") {
        cout << "Nhap xuat xu: ";
        getline(cin, xuatxu);
        menu.push_back(new MonAn(ma, ten, gia, xuatxu));
    }
    else if (loai == "Nuoc") {
        cout << "Nhap han su dung: ";
        getline(cin, hsd);
        menu.push_back(new Nuoc(ma, ten, gia, hsd));
    }
    else {
        cout << "Loai khong hop le!" << endl;
        exit(0);
    }
    system("cls");
    cout <<"Them mon thanh cong ! \n ";
}

void Menu::xoaMon(int i){
    if (i >= 0 && i < menu.size()) {
        delete(menu[i]);
        menu.erase(menu.begin() + i);
    }
}

void Menu::datban(){
        int a = 7;
        int b = 8;
        int matrix[a][b] = {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {9, 10, 11, 12, 13, 14, 15, 16},
        {17, 18, 19, 20, 21, 22, 23, 24},
        {25, 26, 27, 28, 29, 30, 31, 32},
        {33, 34, 35, 36, 37, 38, 39, 40},
        {41, 42, 43, 44, 45, 46, 47, 48},
        {49, 50, 51, 52, 53, 54, 55, 56}
    };
        cout << "\tSo ban hien tai la:" << endl;
    for (int i = 0; i < a; i++) {
    for (int j = 0; j < b; j++) {
        if (matrix[i][j] == 0) {
            cout << "|   ";
        } else {
            if (matrix[i][j] < 10) {
                cout << "| " << matrix[i][j] << " ";
            } else {
                cout << "|" << matrix[i][j] << " ";
            }
        }
        if (j == b - 1) {
            cout << "|";
        }
    }
    cout << endl;
    for (int j = 0; j < b; j++) {
        cout << "+---";
    }
    cout << "+" << endl;
}
    int customerTable;
    cout << "\nMoi nhap so ban muon dat: ";
    cin >> customerTable;
    bool foundTable = false;
    for (int i = 0; i < a && !foundTable; i++) {
        for (int j = 0; j < b && !foundTable; j++) {
            if (matrix[i][j] == customerTable) {
                matrix[i][j] = 'X';
                foundTable = true;
            }
        }
    }
    if (foundTable) {
        cout << "\nBan da dat ban thanh cong!" << endl;
        cout << "\nBan sau khi dat cua khach hang la!\n" << endl;
       for (int i = 0; i < a; i++) {
    for (int j = 0; j < b; j++) {
        if (matrix[i][j] == 'X') {
            cout << "| X ";
        } else if (matrix[i][j] == 0) {
            cout << "|   ";
        } else {
            if (matrix[i][j] < 10) {
                cout << "| " << matrix[i][j] << " ";
            } else {
                cout << "|" << matrix[i][j] << " ";
            }
        }
        if (j == b - 1) {
            cout << "|";
        }
    }
    cout << endl;
    for (int j = 0; j < b; j++) {
        cout << "+---";
    }
    cout << "+" << endl;
}
    } else {
        cout << "So ban khong hop le hoac da co nguoi dat. Vui long thu lai." << endl;
    }
    if (!foundTable) {
        return;
    }
    while (true) {
        char huyDatBan;
        cout << "\nBan co muon huy dat ban nay? (Y/N) ";
        cin >> huyDatBan;
        if (huyDatBan == 'Y' || huyDatBan == 'y') {
            for (int i = 0; i < a; i++) {
                for (int j = 0; j < b; j++) {
                    if (matrix[i][j] == 'X') {
                        matrix[i][j] = customerTable;
                        cout << "\n\tBan da huy ban dat so " << customerTable << endl;
                    cout << "\n\tSo ban sau khi khach hang huy la!\n" << endl;
                for (int k = 0; k < a; k++) {
    for (int l = 0; l < b; l++) {
        if (matrix[k][l] == 'X') {
            cout << "| X ";
        } else if (matrix[k][l] == 0) {
            cout << "|   ";
        } else {
            if (matrix[k][l] < 10) {
                cout << "| " << matrix[k][l] << " ";
            } else {
                cout << "|" << matrix[k][l] << " ";
            }
        }
    }
    cout << "|" << endl;
    for (int l = 0; l < b; l++) {
        cout << "+---";
    }
    cout << "+" << endl;
}
                    cout << "\n\tNhan bat ki phim nao de quay lai menu chinh." << endl;
                    getchar();
                       cin.ignore();
                    system("cls");
                    return; 
                }               
            }
        }
    }               else if (huyDatBan == 'N' || huyDatBan == 'n') {
                        cout << "Cam on ban da dong hanh va ung ho chung toi! " << endl;
                           getchar();
                              cin.ignore();
                    system("cls");
                        return;
            }               
                    else {
                    cout << "Vui long nhap Y hoac N." << endl;
        }
    }                   
}

void Menu::thayDoi(){
    string ID;
    int lc;
    print();
    cout << "ID Mon: ";
    cin >> ID;
    system("cls");
    for (int i=0; i<menu.size(); i++) {
        if (ID == menu[i]->getMa()) {
                cout << "\t*********THAY DOI**********" << endl;
                cout << "\t1.ID" << endl;
                cout << "\t2.Ten" << endl;
                cout << "\t3.Gia tien" << endl;
                cout << "\t4.Xoa mon" << endl;
                cout << "\t5.Thoat" << endl;
                cout << "Chon yeu cau: ";
                cin >> lc;
                switch(lc){
                    case 1:
                        thayDoiID(i);
                        system("cls");
                        cout <<"Chinh sua thanh cong ! \n";
                        break;
                    case 2:
                        thayDoiTen(i);
                        system("cls");
                        cout <<"Chinh sua thanh cong ! \n";
                        break;
                    case 3:
                        thayDoiGia(i);
                        system("cls");
                        cout <<"Chinh sua thanh cong ! \n";
                        break;
                    case 4:
                        xoaMon(i);
                        system("cls");
                        cout <<"Xoa thanh cong ! \n";
                        break;
                    case 5:
                        system("cls");
                        break;
                    default:
                        break;
                }                       
        }
    }
    
}

int main() {
    Menu menu("menu.txt");
    HoaDon* hoaDon = new HoaDon();
    int lc;
    int qty;
        a:
            cout<<"\n\n\t\t\t\t        RESTAURANT MAIN MENU        \n";
            cout<<"\t\t\t\t                                     \n";
            cout<<"\t\t\t\t_____________________________________\n";
            cout<<"\t\t\t\t                                     \n";
            cout<<"\t\t\t\t   |        1) Admin            |\n";
            cout<<"\t\t\t\t   |                            |\n";
            cout<<"\t\t\t\t   |        2) Khach hang       |\n";
            cout<<"\t\t\t\t   |                            |\n";
            cout<<"\t\t\t\t   |        3) Thoat            |\n";
            cout<<"\t\t\t\t   |                            |\n";
            cout<<"\t\t\t\t Please select: ";                
            cin >> lc;
            if(lc == 1) {
                n:
                string email;
                string password;
                cout<<"\t\t\t\t Please Login : \n";
                cout<<"\t\t\t\t Enter email: ";cin>>email;
                cout<<"\t\t\t\t Password: ";cin>>password;
                if(email =="admin" && password =="1"){
                system("cls");
                m:
                cout<<"\t\t\t\t         ADMINISTRATOR MENU         \n";
                cout<<"\t\t\t\t_____________________________________\n";
                cout<<"\t\t\t\t                                     \n";
                cout<<"\t\t\t\t   |   1) Them mon an          |\n";
                cout<<"\t\t\t\t   |                           |\n";
                cout<<"\t\t\t\t   |   2) Chinh sua mon an     |\n";
                cout<<"\t\t\t\t   |                           |\n";
                cout<<"\t\t\t\t   |   3) Quay ve Menu         |\n";
                int choice;
                cout<<"\nPlease select: ";
                cin >> choice;
                switch (choice)
                {
                case 1:
                    system("cls");
                    menu.themMon();
                    break;
                case 2:
                    system("cls");
                    menu.thayDoi();
                    goto m;
                    break;
                case 3:
                    system("cls");
                    goto a;
                    break;
                default:
                    system("cls");
                    cout<<"Invalid choice ! ";
                    goto a;
                 break;
                }
            goto m;
            }
            else{
                system("cls");
                cout<<"Sai email/password ! \n ";
                goto n;
                }
            }
            else if(lc == 2){
                b:
                system("cls");
                int choice;
                cout<<"\t\t\t\t                KHACH HANG            \n";
                cout<<"\t\t\t\t_____________________________________\n";
                cout<<"\t\t\t\t                                     \n";
                cout<<"\t\t\t\t      |   1) Dat mon an      |\n";
                cout<<"\t\t\t\t      |                      |\n";
                cout<<"\t\t\t\t      |   2) Dat ban         |\n";
                cout<<"\t\t\t\t      |                      |\n";
                cout<<"\t\t\t\t      |   3) In hoa don      |\n";
                cout<<"\t\t\t\t      |                      |\n";
                cout<<"\t\t\t\t      |   4) Quay lai        |\n";
                cout<<"\n\t\t\t Please select: ";
                cin>>choice;

                switch (choice)
                {
                case 1:
                    system("cls");
                    menu.print();
                    cout << endl;
                    c:
                    int lc;
                    cout << "Nhap lua chon 1->8 tuong ung voi MENU: ";
                    cin >> lc;
                    cout<<"So luong: "; cin >> qty;
                    if (lc < 1 || lc > menu.getSize()) {
                        cout << "Lua chon khong hop le, vui long nhap lai!\n";
                    }
                    else{
                        MHThucPham* monAn = menu.getMenu(lc-1);
                        hoaDon->themds(monAn,qty);
                        char tt;
                        cout << "Ban co muon chon them mon khac (y/n): ";
                        cin >> tt;
                        if (tt == 'N' || tt == 'n') {
                            system("cls");
                            goto b;
                            break;
                        }
                        else if (tt == 'Y' || tt == 'y'){
                            goto c;
                        }
                        else{
                            break;
                        }
                    }
                    break;
                case 2:
                    system("cls");
                    menu.datban();
                    goto b;
                    break;
                case 3:
                    system("cls");
                    cout<<"\n\n\t\t                ______HOA DON_______                       \n";
                    cout <<"\t\t                        ***                         \n\n" <<endl;
                    hoaDon->print();
                    break;
                case 4:
                    system("cls");
                    goto a;
                    break;
                default:
                    cout<<"Invalid choice ! \n ";
                    break;
                }
            }
            else{
                exit(0);
            }
    return 0;
}
