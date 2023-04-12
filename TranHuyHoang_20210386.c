#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct Node
{
    char Ma_yeu_cau[8];
    int So_luong_nguoi;
    int So_phong;
    char Ma_Khach_san[4];
    int DD, MM, YYYY;
    int So_tre_em;
}Node;
Node *S;
int n = 0, m;

typedef struct Tree
{
    Node Khach_hang;
    struct Tree *left;
    struct Tree *right;
}Tree;
Tree *root;

Tree *MakeNodeTree(Node khach_hang){
    Tree *temp = (Tree *)malloc(sizeof(Tree));
    temp->Khach_hang = khach_hang;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int countNodes(Tree* r) {
    if (r == NULL) return 0;
    else return countNodes(r->left) + 1 + countNodes(r->right);
}

Tree *Insert(Tree * r, Node khach_hang){
    if(r == NULL){
        return  MakeNodeTree(khach_hang);
    }
    else{
        if(strcmp(r->Khach_hang.Ma_yeu_cau, khach_hang.Ma_yeu_cau) < 0){
            r->right = Insert(r->right, khach_hang);
            return r;
        }
        else{
            r->left = Insert(r->left, khach_hang);
            return r;
        }
    }
}

Tree* find(Tree* r, char* ma_yeu_cau){
    if(r == NULL) return NULL;
    int c = strcmp(r->Khach_hang.Ma_yeu_cau, ma_yeu_cau);
    if(c == 0) return r;
    if(c < 0) return find(r->right, ma_yeu_cau);
    return find(r->left, ma_yeu_cau);
}

Tree *findMin(Tree* r){
    if(r == NULL) return NULL;
    else{
        if(r->left == NULL){
            return r;
        }
        else{
            return findMin(r->left);
        }
    }
}

Tree *Delete(Tree *r, char* ma_yeu_cau){
    if(r == NULL) return NULL;
    int c = strcmp(r->Khach_hang.Ma_yeu_cau, ma_yeu_cau);
    if(c > 0) r->left = Delete(r->left , ma_yeu_cau);
    else if(c < 0) r->right = Delete(r->right, ma_yeu_cau);
    else{
        if(r->left != NULL && r->right != NULL){
            Tree* tmp = findMin(r->right);
            r->Khach_hang = tmp->Khach_hang;
            r->right = Delete(r->right, tmp->Khach_hang.Ma_yeu_cau);
        }else{
            Tree* tmp = r;
            if(r->left == NULL) r = r->right; else r = r->left;
            free(tmp);
        }
    }
    return r;
}

// void inOrder(Tree* r){
//     if(r == NULL) return;
//     inOrder(r->left);
//     printf("%s  %02d-%02d-%02d %02d:%02d:%02d\n", r->Xe.Bien_so, r->Xe.YYYY, r->Xe.MM, r->Xe.DD, r->Xe.hh, r->Xe.mm, r->Xe.ss);
//     inOrder(r->right);
// }

void inOrderFile(Tree* r, FILE *f){
    if(r == NULL) return;
    inOrderFile(r->left, f);
    fprintf(f, "%s %d %d %s %02d-%02d-%02d %d\n", r->Khach_hang.Ma_yeu_cau, r->Khach_hang.So_luong_nguoi, r->Khach_hang.So_phong, r->Khach_hang.Ma_Khach_san, r->Khach_hang.DD, r->Khach_hang.MM, r->Khach_hang.YYYY, r->Khach_hang.So_tre_em);
    inOrderFile(r->right, f);
}

void DS_to_Tree(){
    for(int i = 0; i < n; i++){
        root = Insert(root, S[i]);
    }
}

void freeTree(Tree *r){
    if(r == NULL) return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

void Menu(){
    printf("\n===============================================================\n");
    printf("Chuong trinh quan ly bai xe\n");
    printf("Vui long chon mot trong cac chuc nang sau\n");
    printf("[1] Doc du lieu tu file log\n");
    printf("[2] Du lieu khong hop le\n");
    printf("[3] Tim kiem thong tin\n");
    printf("[4] Cap nhat yeu cau\n");
    printf("[5] Huy yeu cau\n");
    printf("[6] Ghi ra file output\n");
    printf("[7] Yeu cau khong hop le thoi gian\n");
    printf("[8] Yeu cau qua som\n");
    printf("[9] Thoat\n");
    printf("===============================================================\n");
    printf("Lua chon cua ban la: \n");
}

//Task 1
void Read_Log(){
    int k;
    FILE *f = fopen("booking_orders.txt", "r");
    if(f == NULL){
        printf("Can not open this file\n");
        return;
    }
    else{
        while (!feof(f)){
            Node temp;
            fscanf(f, "%d", &k);
            for(int i = 1; i <= k; i++){
                fscanf(f,"%s %d %d %s %d-%d-%d %d", temp.Ma_yeu_cau, &temp.So_luong_nguoi, &temp.So_phong, temp.Ma_Khach_san, &temp.DD, &temp.MM, &temp.YYYY, &temp.So_tre_em);
            S[n] = temp;
            n++;
            }
        } 
    }
    printf("So luong yeu cau la %d\n", k);
}

//Task 2
void Yeu_cau_KHONG_hop_le(){
    int cnt = 0;
    for(int i = 0; i < n; i++){
        if(S[i].So_tre_em >= S[i].So_luong_nguoi){
            cnt++;
        }
    }
    printf("So yeu cau khong hop le la %d\n", cnt);
}

//Task 3
void Tim_kiem_thong_tin(){
    char ma_yc[8];
    printf("Nhap ma yeu cau: ");
    scanf("%s", ma_yc);
    Tree *tmp = find(root, ma_yc);
    if(tmp == NULL){
        printf("Not found\n");
    }
    else{
        printf("%s %d %d %s %02d-%02d-%02d %d\n", tmp->Khach_hang.Ma_yeu_cau, tmp->Khach_hang.So_luong_nguoi, tmp->Khach_hang.So_phong, tmp->Khach_hang.Ma_Khach_san, tmp->Khach_hang.DD, tmp->Khach_hang.MM, tmp->Khach_hang.YYYY, tmp->Khach_hang.So_tre_em);
    }
}

//Task 4
void Cap_nhat_yeu_cau(){
    char ma_yc[8];
    printf("Nhap ma yeu cau: ");
    scanf("%s", ma_yc);
    Tree *tmp = find(root, ma_yc);
    if(tmp == NULL){
        printf("Not found\n");
    }
    else{
        printf("Ban hay cap nhat ngay, thang, nam (dinh dang: DD-MM-YYYY): ");
        int d, m, y;
        scanf("%d-%d-%d", &d, &m, &y);
        tmp->Khach_hang.DD = d;
        tmp->Khach_hang.MM = m;
        tmp->Khach_hang.YYYY = y;
        printf("Ban hay cap nhap so luong nguoi: ");
        int so_nguoi;
        scanf("%d", &so_nguoi);
        printf("Ban hay cap nhat so tre em: ");
        int tre_em;
        scanf("%d", &tre_em);
        if(so_nguoi <= tre_em){
            printf("Invalid\n");
        }
        else{
            tmp->Khach_hang.So_luong_nguoi = so_nguoi;
            tmp->Khach_hang.So_tre_em = tre_em;
            printf("Update\n");
        }
    }
}

//Task 5
void Huy_yeu_cau(){
    printf("Hay nhap ma can huy: ");
    char ma_yc[8];
    scanf("%s", ma_yc);
    Tree *tmp = find(root, ma_yc);
    if(tmp == NULL){
        printf("Not found\n");
    }
    else{
        root = Delete(root, ma_yc);
        printf("Delete\n");
    }
}

//Task 6
void Ghi_ra_file_output(){
    int cnt_ma_yeucau = 0;
    FILE *f = fopen("booking_output.txt", "w");
    if(f == NULL){
        printf("Can not open this file\n");
    }
    else{
        inOrderFile(root, f);
        printf("So luong yeu cau da duoc ghi vao file la: %d", countNodes(root));
    }
    fclose(f);
}

//Task 7: OP1
// void Khach_san_thue_nhieu_nhat(){
//     int 
// }

//Task 8: op2
void Yeu_cau_hop_le_thoi_gian(){
    printf("Nhap ngay hien tai (DD-MM-YYYY): ");
    int d, m, y;
    scanf("%d-%d-%d", &d, &m, &y);
    printf("Cac ma yeu cau KHONG hop le\n");
    for(int i = 0; i < n; i++){
        if(S[i].YYYY < y){
            printf("%s\n", S[i].Ma_yeu_cau);
        }
        else if(S[i].YYYY == y){
            if(S[i].MM < m){
                printf("%s\n", S[i].Ma_yeu_cau);
            }
            else if(S[i].MM == m){
                if(S[i].DD < d){
                    printf("%s\n", S[i].Ma_yeu_cau);
                }
            }
        }
    }
}

//Task 9 OP 3
void Yeu_cau_qua_som(){
    printf("Nhap ngay hien tai (DD-MM-YYYY): ");
    int d, m, y;
    scanf("%d-%d-%d", &d, &m, &y);
    
    for(int i = 0; i < n; i++){
        struct tm time1 = {0};
        struct tm time2 = {0};

        time1.tm_year = S[i].YYYY - 1900;
        time1.tm_mon = S[i].MM - 1;
        time1.tm_mday = S[i].DD;
        time1.tm_hour = 0;
        time1.tm_min = 0;
        time1.tm_sec = 0;

        time2.tm_year = y - 1900;
        time2.tm_mon = m - 1;
        time2.tm_mday = d;
        time2.tm_hour = 0;
        time2.tm_min = 0;
        time2.tm_sec = 0;
    
        time_t t1 = mktime(&time1);
        time_t t2 = mktime(&time2);

        double diff = difftime(t1, t2);
        if((int)diff > 60){
            printf("%s\n", S[i].Ma_yeu_cau);
        }
    }
}
int main(){
    S = (Node*)malloc(1000*sizeof(Node));
    if(S == NULL){ 
        printf("ERORR: can't dynamically allocate memory!!!");
        return 1;
    }
    root = NULL;
    int count_DS_to_Tree = 0;
    int key;
    while(1){
        Menu();
        scanf("%d",&key);
        switch (key)
        {
        case 1:
            if(count_DS_to_Tree == 0){
                Read_Log();
                DS_to_Tree();
                count_DS_to_Tree++; // chi nap tu S vao Tree 1 lan duy nhat
            }
            break;
        case 2:
            Yeu_cau_KHONG_hop_le();
            break;
        case 3:
            Tim_kiem_thong_tin();
            break;
        case 4: 
            Cap_nhat_yeu_cau();
            break;
        case 5:
            Huy_yeu_cau();
            break;
        case 6:
            Ghi_ra_file_output();
            break;
        case 7:
            Yeu_cau_hop_le_thoi_gian();
            break;
        case 8:
            Yeu_cau_qua_som(); 
            break;
        case 9:
            freeTree(root);
            free(S);
            exit(1);
        default:
            break;
        }
    }     
}
