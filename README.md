# Quan Ly Bai Giu Xe - C Console

Ung dung console mo phong quan ly bai giu xe 12 vi tri: tiep nhan xe, gan o trong, tim xe, xu ly xe ra, tinh phi theo thoi gian thuc, luu lich su CSV va thong ke doanh thu.

## Yeu cau
- GCC hoac Clang ho tro C11.
- Chay tu thu muc goc repository de duong dan `data/...` hoat dong.
- Khong can thu vien ngoai.

## Bien dich
Linux/macOS:
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/*.c -o parking
```

Windows (MinGW):
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src\*.c -o parking.exe
```

## Chay
```bash
./parking
```
Windows: `parking.exe`

## Chuc nang
1. Xe vao: nhap bien so, loai xe XM/OTO, tu dong gan o trong.
2. Xe ra: tim xe, tinh thoi gian bang `difftime`, tinh phi, ghi lich su va giai phong o.
3. Hien thi so do 12 vi tri tren console.
4. Tim xe dang gui.
5. Xem lich su gui xe trong `data/lichsu.csv`.
6. Thong ke so luot xe da hoan tat va tong doanh thu.
7. Luu xe dang gui vao `data/xe_dang_gui.csv` de nap lai khi mo lai chuong trinh.

## Bang gia minh hoa
- Xe may (XM): 5.000 VND/gio hoac phan gio.
- O to (OTO): 20.000 VND/gio hoac phan gio.
- Toi thieu 1 gio; lam tron len theo gio.

## Cau truc thu muc
- `include/parking.h`: cau truc du lieu va khai bao ham.
- `src/main.c`: menu va dieu phoi.
- `src/parking.c`: quan ly vi tri va so do.
- `src/operations.c`: nghiep vu xe vao, xe ra, tim xe.
- `src/time_fee.c`: thoi gian va tinh phi.
- `src/storage.c`: doc/ghi CSV.
- `src/statistics.c`: thong ke.
- `tests/test_cases.csv`: danh sach tinh huong kiem thu thu cong.
- `data/`: du lieu runtime, tu tao khi chay.

## Gioi han
Day la mo hinh hoc tap, khong ket noi camera, RFID hay barrier that. Nhan dien bien so va quet the duoc mo phong bang nhap ban phim. Thong ke hien tai la tong lich su, chua phan tach theo ca/ngay. Bang gia chi la gia minh hoa va can thay theo yeu cau bai tap thuc te.

## Quy trinh lam viec nhom
Moi thanh vien nen clone repository, tao nhanh rieng, commit phan viec minh thuc hien, tao pull request va ghi ro noi dung thay doi. Khong dung chung tai khoan de tao commit thay cho thanh vien khac.
