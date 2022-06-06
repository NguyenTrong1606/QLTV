
// lay max width, height cua man hinh
int w = GetSystemMetrics(SM_CXSCREEN);
int h = GetSystemMetrics(SM_CYSCREEN);

Window Window;
SubWindow subWindow;
int curMenu = 0, curMenuMuonTra;
int curItem = -1, curItemSach = -1, curDauSach = -1, curSach = -1;
int curItemDG = -1, curDG = -1;
int curItemMT = -1, curMT = -1;
DocGia *curDGMT = NULL;
DauSach *curDSMT = NULL;
Sach *curSachMT = NULL;
Node_ID *nodeStart = NULL;	// random ID doc gia
// toa do con tro chuot hien tai
int mx = -1, my = -1;
int totalPageDauSach = 1, curPageDauSach = 1;
int totalPageSach = 1, curPageSach = 1;

int totalPageDG = 1, curPageDG = 1;
int totalPageDGQuaHan = 1, curPageDGQuaHan = 1;

int totalNhapSach = 0, curNhapSach = 0;
int startIndexSach = -1;

bool sortDGByName = false;
bool canMT = false; // Doc Gia co the muon sach hay khong?
bool canEditTrangThai = true; 
bool isChoose = false;
EditText *Edit = NULL;

// hoanh do x cua Dau Sach
int XDS[7] = {10, 200, 500, 600, 800, 900, 1100};
// X Danh Muc Sach
int XDMS[4] = {1120, 1350, 1600, w-20};
// X Danh sach Doc Gia
int XDG[7] = {10, 100, 400, 550, 700, 900, 1100};
// X Muon Tra sach
int XMT[5] = {50, 200, 525, 700, 900};
// X Top 10
int XTT[] = {180, 260, 450, 650, 880, 1180, 1280, 1430, 1630};

char *TrangThaiSach[15] = {"CHO MUON DUOC", "DA CHO MUON", "DA BI MAT"};
char *PhaiDocGia[5] = {"NAM", "NU"};
char *TTTDocGia[10] = {"KHOA", "HOAT DONG"};
char TTMuonTra[][10] = {"DANG MUON", "DA TRA", "LAM MAT"};

char mess[50];

bool mclick = false;

DS_DocGia DSDG;
DS_DauSach DSDS;
NodeDocGia *TreeDocGia = NULL;

char AppTitle[] = "QUAN LY THU VIEN";
char DauSachTitle[] = "DANH SACH DAU SACH";
char ThemDauSach[] = "THEM DAU SACH";
char HieuChinhDauSach[] = "HIEU CHINH DAU SACH";
char ThemSach[] = "THEM SACH: ";
char NhapSach[] = "NHAP SACH";
char HieuChinhSach[] = "HIEU CHINH SACH";
char ThongBao[] = "THONG BAO:";
char DanhMucSach[80] = "DANH MUC SACH";
char DocGiaTitle[] = "DANH SACH DOC GIA";
char ThemDocGia[] = "THEM DOC GIA";
char HieuChinhDocGia[] = "HIEU CHINH DOC GIA";
char XoaDocGia[] = "XOA DOC GIA";
char MuonSach[] = "MUON SACH";
char TraSach[] = "TRA SACH";
char TopTen[] = "TOP 10 DAU SACH DUOC MUON NHIEU NHAT";
char DSDM[] = "CAC SACH DANG MUON";
// Button Main Menu
int btnHei = 200, btnWid = 450, btnSpace = 250, btnY = 150;
ButtonMenu btnQLDauSach(100, w/3-btnWid/2, btnY + btnSpace, btnWid, btnHei, "QUAN LY DAU SACH", 0);
ButtonMenu btnQLDocGia(101, w/3-btnWid/2, btnY + 2*btnSpace, btnWid, btnHei, "QUAN LY DOC GIA", 0);
ButtonMenu btnQLSach(102, w/3*2-btnWid/2, btnY + btnSpace, btnWid, btnHei, "MUON TRA SACH", 0);
ButtonMenu btnThoat(104, w/3*2-btnWid/2, btnY + 2*btnSpace, btnWid, btnHei, "THOAT", 0);


// Button Dau Sach
Button btnQuayVe(201, 10, 10, 100, 50, "< MENU", 0);
Button btnClearTimDauSach(202, 800, 70, 100, 50, "CLEAR", 0);
Button btnPrevDauSach(203, 10, 770, 150, 50, "Trang truoc", 0);
Button btnNextDauSach(204, XDS[6]-150, 770, 150, 50, "Trang sau", 0);

EditText edTimDauSach(1000, 50, 70, 700, 50, "Tim dau sach:", "", "");


// Them Dau Sach
EditText edThemISBN(1002, XDS[6]+50, 290, 700, 40, "ISBN :","","VD: TDK");
EditText edThemTenSach(1003, XDS[6]+50, 340, 700, 40, "Ten sach :","","VD: TAY DU KI");
EditText edThemSoTrang(1004, XDS[6]+50, 390, 700, 40, "So trang :","","VD: 3000");
EditText edThemTacGia(1005, XDS[6]+50, 440, 700, 40, "Tac gia :","","VD: NGO THUA AN");
EditText edThemNXB(1006, XDS[6]+50, 490, 700, 40, "Nam xuat ban :","","VD: 1880");
EditText edThemTheLoai(1007, XDS[6]+50, 540, 700, 40, "The loai :","","VD: GIA TUONG");
Button btnClr(230, (w-15+XDS[6])/2 + 100, 590, 150, 50, "HUY", 0);
Button btnThemDauSach(205, (w-15+XDS[6])/2 - 100, 590, 150, 50, "THEM", 0);

// Hieu Chinh Dau Sach
EditText edHieuChinhISBN(1008, XDS[6]+50, 290, 700, 40, "ISBN :","","");
EditText edHieuChinhTenSach(1009, XDS[6]+50, 340, 700, 40, "Ten sach :","","");
EditText edHieuChinhSoTrang(1010, XDS[6]+50, 390, 700, 40, "So trang :","","");
EditText edHieuChinhTacGia(1011, XDS[6]+50, 440, 700, 40, "Tac gia :","","");
EditText edHieuChinhNXB(1012, XDS[6]+50, 490, 700, 40, "Nam xuat ban :","","");
EditText edHieuChinhTheLoai(1013, XDS[6]+50, 540, 700, 40, "The loai :","","");

Button btnHieuChinhDauSach(206, (w-15+XDS[6])/2 - 100, 590, 150, 50, "HIEU CHINH", 0);

// Xoa Dau Sach
Button btnXoaDauSach(210, (w-15+XDS[6])/2 + 100, 590, 150, 50, "XOA DAU SACH",0);

// Danh Muc Sach
Button btnPrevDanhMucSach(207, XDMS[0], 550, 150, 50, "Trang truoc", 0);
Button btnNextDanhMucSach(208, XDMS[3]-150, 550, 150, 50, "Trang sau", 0);
Button btnBackToThemDauSach(210, XDS[6]+20, 10, 100, 50, "< CLOSE", 0);
// Nhap Sach
EditText edNhapSoLuongSach(1016, XDMS[0]+30, 700, 700, 40, "So luong sach :", "", "");
Button btnNhapSoLuongSach(217, (XDMS[0]+XDMS[3])/2-50, 760, 100, 50, "NHAP", 0);
// Them Sach
EditText edThemMaSach(1014, XDMS[0]+10, 650, 600, 40, "Ma sach :", "", "");
EditText edThemTrangThaiSach(1015, XDMS[0]+10, 700, 600, 40, "Trang thai [0,1,2] ", "", "", TrangThaiSach);
EditText edThemViTriSach(1017, XDMS[0]+10, 750, 600, 40, "Vi tri :", "", "");
Button btnThemSach(209, XDMS[0] + 660, 700-5, 100, 50, "THEM", 0);

// Hieu Chinh Sach
EditText edHieuChinhMaSach(1014, XDMS[0]+10, 650, 600, 40, "Ma sach:", "", "");
EditText edHieuChinhTrangThaiSach(1015, XDMS[0]+10, 700, 600, 40, "Trang thai [0,1,2]", "", "", TrangThaiSach);
EditText edHieuChinhViTriSach(1015, XDMS[0]+10, 750, 600, 40, "Vi tri :", "", "");
Button btnHieuChinhSach(217, XDMS[0] + 660, 690, 100, 50, "SUA", 0);
Button btnBackToNhapSach(210, XDMS[0] + 660, 650, 100, 35, "< THEM", 0);

// Xoa Sach
Button btnXoaSach(218, XDMS[0] + 660, 750-5, 100, 50, "XOA", 0);

// Danh sach Doc Gia
Button btnTatCaDocGia(211, 650, 115, 100, 50, "TAT CA", 0);
Button btnDocGiaQuaHan(212, 750, 115, 100, 50, "QUA HAN", 0);
Button btnSapXepTen(213, 200, 115, 100, 50, "TEN", 0);
Button btnSapXepMaThe(214, 300, 115, 100, 50, "MA THE", 0);
Button btnPrevDocGia(215, 10, 880, 150, 50, "Trang truoc", 0);
Button btnNextDocGia(216, XDG[5]-150, 880, 150, 50, "Trang sau", 0);

Button btnPrevDocGiaQH(215, 10, 880, 150, 50, "Trang truoc", 0);
Button btnNextDocGiaQH(216, XDG[6]-150, 880, 150, 50, "Trang sau", 0);

// Them Doc Gia
EditText edThemMaTheDocGia(1002, XDG[6]+50, 300, 700, 40, "Ma the:","","AUTO");
EditText edThemHoDocGia(1003, XDG[6]+50, 350, 700, 40, "Ho va ten dem:","","VD: Nguyen Van");
EditText edThemTenDocGia(1004, XDG[6]+50, 400, 700, 40, "Ten:","","VD: Trong");
EditText edThemPhaiDocGia(1005, XDG[6]+50, 450, 700, 40, "Phai [0,1]:","","0: Nam   -   1: Nu", PhaiDocGia);
EditText edThemTrangThaiTheDocGia(1006, XDG[6]+50, 500, 700, 40, "Trang thai [0,1]:","1","0: Khoa  -  1: Hoat dong", TTTDocGia);

Button btnThemDocGia(205, (XDG[6]+w-15+20)/2 - 75, 570, 150, 50, "THEM", 0);

// Hieu Chinh Doc Gia
EditText edHieuChinhMaTheDocGia(1002, XDG[6]+50, 300, 700, 40, "Ma the:","","KHONG THE SUA");
EditText edHieuChinhHoDocGia(1003, XDG[6]+50, 350, 700, 40, "Ho va ten dem:","","VD: Nguyen Van");
EditText edHieuChinhTenDocGia(1004, XDG[6]+50, 400, 700, 40, "Ten:","","VD: Trong");
EditText edHieuChinhPhaiDocGia(1005, XDG[6]+50, 450, 700, 40, "Phai [0,1]:","","0: Nam   -   1: Nu", PhaiDocGia);
EditText edHieuChinhTrangThaiTheDocGia(1006, XDG[6]+50, 500, 700, 40, "Trang thai [0,1]:","1","0: Khoa  -  1: Hoat dong", TTTDocGia);

Button btnHieuChinhDocGia(205, (XDG[6]+w-15+20)/2 - 75, 570, 150, 50, "HIEU CHINH", 0);
Button btnBackToThemDocGia(210, XDG[6]+20, 10, 100, 50, " CLOSE", 0);

// Xoa doc gia
Button btnXacNhanXoaDocGia(220, XDG[6]+200, 580, 100, 50, "XOA", 0);
Button btnHuyXoaDocGia(220, w-15-280, 580, 100, 50, "HUY", 0);

// Muon Tra Sach
Button btnBackToMenu(230, 20, 20, 200, 70, "  < MENU", -1);
Button btnMuonSach(231, 450, 20, 200, 70, "  MUON SACH", -1);
Button btnTraSach(232, 250+((w-250)/2-100), 20, 200, 70, "  TRA SACH", -1);
Button btnTopTen(233, w-400, 20, 200, 70, "  TOP 10", -1);

// Muon sach
EditText edNhapMaDGMuonSach(1111, 135, 230, 600, 50, "Nhap ma the :", "", "VD:13033");
EditText edNhapMaSachMuonSach(1112, w/2 + 120, 230, 600, 50, "Nhap ma sach :", "", "VD:DPTK-1");
EditText edNhapNgayMuonSach(1113, w/2 + 130, 600, 600, 50, "Ngay muon :", "", "01/01/2022");
Button btnTimMaDG(241, 785, 230, 100, 50, "TIM", 0);
Button btnTimMaSach(242, w/2 + 770, 230, 100, 50, "TIM", 0);
Button btnXacNhanMuonSach(243, 1350, 700, 150, 50, "MUON SACH", 0);

// Tra sach
EditText edNhapNgayTraSach(1114, w/2 + 180, 600, 600, 50, "Ngay tra :", "", "01/01/2022");
Button btnXacNhanTraSach(244, w/2 + 180, 700, 150, 50, "TRA SACH", 0);

Button btnLamMatSach(300, w - 380, 700, 200, 50, "LAM MAT SACH?", 0);

Button btnXacNhanLamMatSach(301, w/2+250, 800, 200, 50, "XAC NHAN", 0);
Button btnHuyLamMatSach(302, w-15-400, 800, 200, 50, "HUY", 0);

void ClearScreen();
void DrawMenu();
void ButtonEffect(Button &btn);
void MenuEvent();
void Event();
void SetMenuSelect(int menuID);
void DrawDanhSachDauSach();
void RunDauSach();
void DauSachEvent();
void DrawBorderList();
void DrawBorderListSach();
void DrawList();
void DrawThemDauSach();
void DrawHieuChinhDauSach();
void DrawDanhMucSach();
void DrawNhapSach();
void ClearLayoutListDauSach();
void ClearLayoutSach();
void ClearLayoutDanhMucSach();
void ClearContentHieuChinhSach();
void ItemEvent();
void AutoCreateMaSach();
int GetItemPosition(int y);
int GetItemSachPosition(int y);
void ClickEvent();
void ItemLeftMouseClick();
void ItemRightMouseClick();
void KbEvent();
void DrawItemDauSach(int, int);
void DrawItemSach(Sach &sach, int i);
void ClearContentThemDauSach();

void RunDocGia();
void ClearRightLayoutDocGia();
void DocGiaEvent();
void DrawDanhSachDocGia();
void DrawBorderDSDocGia();
void DrawListDocGia(bool reload = false);

void Scan(EditText* &txt, int maxn, ScanType type, int strartLimit = 0, int endLimit = 0);
void ScanTimDauSach(EditText* &txt, int &n, int maxn, char c);
void ScanTextNumber(EditText* &txt, int &n, char c);
void ScanTextSpace(EditText* &txt, int &n, char c);
void ScanTextOnly(EditText* &txt, int &n, char c);
void ScanNumber(EditText* &txt, int &n, char c);
void ScanNumberGreater0(EditText* &txt, int &n, char c);
void ScanDate(EditText* &txt, int &n, char c);
void ScanLimit(EditText* &txt, int &n, char c, int start, int end);
void ScanMaSach(EditText* &txt, int &n, char c);
void ClearStream();

void DrawThemDocGia(bool genNewID = true);
void DrawItemDocGia(DocGia &docgia, int i);
void DrawItemDocGiaQuaHan(DocGia &docgia, int soNgayQH, int i);
bool ChecHieuCHinhDocGia();
bool CheckThemDocGia();
void ClearContentHieuChinhDocGia();
void ClearContentThemDocGia();
void DuyetDGTheoMaThe(NodeDocGia* &node, int &i);
void ItemDocGiaEvent();
int GetItemDocGiaPosition(int y);
void ClearLayoutListDocGia();
void DrawHieuChinhDocGia();
void ItemDGLeftMouseClick();
bool CheckHieuChinhDocGia();
void ButtonSwitchClick();
void ItemDGRightMouseClick();
void DrawXoaDocGia(int i);
void ClearLayoutListDocGiaQuaHan();
void DrawBorderDSDocGiaQuaHan();
void DeleteMemoryDocGia(NodeDocGia* &node);

void RunMuonTra();
void MuonTraEvent();
void SetMenuMuonTraSelect(int menuID);
void ClearLayoutMainMuonTra();
void DrawBorderMuonTra();
void DrawMuonSach();
void DrawTraSach();
void DrawTopTen();
void DrawThongTinDocGia();
void ClearLayoutLeftMuonTra();
void ClearLayoutRightMuonTra();
void DrawThongTinSach();
bool CheckDate(char* s);
void ItemMTEvent();
void DrawItemMT(int i);
void ItemMTClick();
void DrawThongTinSachTra(int itemMT);
int TotalDocGia(NodeDocGia* &TreeDG);
void DrawLamMatSach();

void DemSoLanMuonSach(DocGia docgia, TopSach &topsach);
void DuyetDocGia(NodeDocGia* &nodeDG, TopSach &topsach);

void MoveToNextEditText();
void MoveToPrevEditText();

void KbEvent(){
	if(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT)){
		ClearStream();
		return;
	}
	
	if(GetAsyncKeyState(VK_DOWN)){
		ClearStream();
		if(Edit != NULL){
			int n = strlen(Edit->content);
			Edit->draw();
			Edit->content[n] = '\0';
			MoveToNextEditText();
		}
		return;
	}else if(GetAsyncKeyState(VK_UP)){
		ClearStream();
		if(Edit != NULL){
			int n = strlen(Edit->content);
			Edit->draw();
			Edit->content[n] = '\0';
			MoveToPrevEditText();
		}
		return;
	}
	
	if(Edit != NULL){
		int n = strlen(Edit->content);
		Edit->content[n] = '_';
		Edit->draw();
		Edit->content[n] = '\0';	
		
		if(curMenu == btnQLDauSach.id){
			if(Edit == &edTimDauSach){
				Scan(Edit, 50, FIND_DS);
			}
			
			if(Window == THEM_DAU_SACH){
				if(Edit == &edThemISBN){
					Scan(Edit, 10, ISBN);
				}else if(Edit == &edThemTenSach){
					Scan(Edit, 50, TEXT_NUMBER);
				}else if(Edit == &edThemSoTrang){
					Scan(Edit, 5, ONLY_NUMBER_GREATER_0);
				}else if(Edit == &edThemTacGia){
					Scan(Edit, 50, SPACE_TEXT);
				}else if(Edit == &edThemNXB){
					Scan(Edit, 4, ONLY_NUMBER_GREATER_0);
				}else if(Edit == &edThemTheLoai){
					Scan(Edit, 50, SPACE_TEXT);
				}
				
			}else if(Window == HIEU_CHINH_DAU_SACH){
				if(Edit == &edHieuChinhISBN){
					Scan(Edit, 10, ISBN);
				}else if(Edit == &edHieuChinhTenSach){
					Scan(Edit, 50, TEXT_NUMBER);
				}else if(Edit == &edHieuChinhSoTrang){
					Scan(Edit, 5, ONLY_NUMBER_GREATER_0);
				}else if(Edit == &edHieuChinhTacGia){
					Scan(Edit, 50, SPACE_TEXT);
				}else if(Edit == &edHieuChinhNXB){
					Scan(Edit, 4, ONLY_NUMBER_GREATER_0);
				}else if(Edit == &edHieuChinhTheLoai){
					Scan(Edit, 50, SPACE_TEXT);
				}
				
			}else if(Window == DANH_MUC_SACH){
				if(subWindow == NHAP_SACH){
					if(Edit == &edNhapSoLuongSach){
						Scan(Edit, 2, ONLY_NUMBER_GREATER_0);
					}
				}else if(subWindow == THEM_SACH){
					if(Edit == &edThemTrangThaiSach){
						Scan(Edit, 1, LIMIT_CHARACTER, '0', '2');
					}else if(Edit == &edThemViTriSach){
						Scan(Edit, 18, TEXT_NUMBER);
					}
				}else if(subWindow == HIEU_CHINH_SACH){
					if(Edit == &edHieuChinhTrangThaiSach){
						Scan(Edit, 1, LIMIT_CHARACTER, '0', '2');
					}else if(Edit == &edHieuChinhViTriSach){
						Scan(Edit, 20, TEXT_NUMBER);
					}
				}
				
			}
		}else if(curMenu == btnQLDocGia.id){
			if(Window == THEM_DOC_GIA){
				if(Edit == &edThemHoDocGia){
					Scan(Edit, 30, SPACE_TEXT);
				}else if(Edit == &edThemTenDocGia){
					Scan(Edit, 10, ONLY_TEXT);
				}else if(Edit == &edThemPhaiDocGia){
					Scan(Edit, 1, LIMIT_CHARACTER, '0', '1');
				}else if(Edit == &edThemTrangThaiTheDocGia){
					Scan(Edit, 1, LIMIT_CHARACTER, '0', '1');
				}
				
			}else if(Window == HIEU_CHINH_DOC_GIA){
				if(Edit == &edHieuChinhHoDocGia){
					Scan(Edit, 30, SPACE_TEXT);
				}else if(Edit == &edHieuChinhTenDocGia){
					Scan(Edit, 10, ONLY_TEXT);
				}else if(Edit == &edHieuChinhPhaiDocGia){
					Scan(Edit, 1, LIMIT_CHARACTER, '0', '1');
				}else if(Edit == &edHieuChinhTrangThaiTheDocGia){
					Scan(Edit, 1, LIMIT_CHARACTER, '0', '1');
				}
			}else if(Window == XOA_DOC_GIA){
				
			}
		}else if(curMenu == btnQLSach.id){
			if(Edit == &edNhapMaDGMuonSach){
				Scan(Edit, 5, ONLY_NUMBER);
			}else if(Edit == &edNhapMaSachMuonSach){
				Scan(Edit, 18, MASACH);
			}else if(Edit == &edNhapNgayMuonSach){
				Scan(Edit, 10, DATE_TIME);
			}
			
			if(Edit == &edNhapNgayTraSach){
				Scan(Edit, 10, DATE_TIME);
			}
		}
	}else{
		ClearStream();
	}
}

void SetMenuSelect(int menuID){
	if(curMenu != menuID){
		curMenu = menuID;
		ClearScreen();
		
		if(curMenu == 0){
			DrawMenu();
		}else if(menuID == btnQLDauSach.id){
			RunDauSach();
		}else if(menuID == btnQLDocGia.id){
			RunDocGia();
		}else if(menuID == btnQLSach.id){
			RunMuonTra();
		}
	}	
}

void ButtonEffect(Button &btn){
	if(btn.isChoose) return;
	
	if(btn.isMouseHover(mousex(), mousey())){
		if(btn.isHover == false){
			btn.isHover = true;
			btn.draw();
		}
	}else{
		if(btn.isHover == true){
			btn.isHover = false;
			btn.draw(); 
		} 
	} 
}
void ButtonEffect(ButtonMenu &btn){
	if(btn.isChoose) return;
	
	if(btn.isMouseHover(mousex(), mousey())){
		if(btn.isHover == false){
			btn.isHover = true;
			btn.draw();
		}
	}else{
		if(btn.isHover == true){
			btn.isHover = false;
			btn.draw(); 
		} 
	} 
}

void MoveToNextEditText(){
	if(Edit == &edThemISBN) Edit = &edThemTenSach;
	else if(Edit == &edThemTenSach) Edit = &edThemSoTrang;
	else if(Edit == &edThemSoTrang) Edit = &edThemTacGia;
	else if(Edit == &edThemTacGia) Edit = &edThemNXB;
	else if(Edit == &edThemNXB) Edit = &edThemTheLoai;

	
	if(Edit == &edHieuChinhTenSach) Edit = &edHieuChinhSoTrang;
	else if(Edit == &edHieuChinhSoTrang) Edit = &edHieuChinhTacGia;
	else if(Edit == &edHieuChinhTacGia) Edit = &edHieuChinhNXB;
	else if(Edit == &edHieuChinhNXB) Edit = &edHieuChinhTheLoai;


	if(Edit == &edThemMaTheDocGia) Edit = &edThemHoDocGia;
	else if(Edit == &edThemHoDocGia) Edit = &edThemTenDocGia;
	else if(Edit == &edThemTenDocGia) Edit = &edThemPhaiDocGia;
	else if(Edit == &edThemPhaiDocGia) Edit = &edThemTrangThaiTheDocGia;

	
	if(Edit == &edHieuChinhHoDocGia) Edit = &edHieuChinhTenDocGia;
	else if(Edit == &edHieuChinhTenDocGia) Edit = &edHieuChinhPhaiDocGia;
	else if(Edit == &edHieuChinhPhaiDocGia) Edit = &edHieuChinhTrangThaiTheDocGia;

}

void MoveToPrevEditText(){

	if(Edit == &edThemTenSach) Edit = &edThemISBN;
	else if(Edit == &edThemSoTrang) Edit = &edThemTenSach;
	else if(Edit == &edThemTacGia) Edit = &edThemSoTrang;
	else if(Edit == &edThemNXB) Edit = &edThemTacGia;
	else if(Edit == &edThemTheLoai) Edit = &edThemNXB;
	

	if(Edit == &edHieuChinhSoTrang) Edit = &edHieuChinhTenSach;
	else if(Edit == &edHieuChinhTacGia) Edit = &edHieuChinhSoTrang;
	else if(Edit == &edHieuChinhNXB) Edit = &edHieuChinhTacGia;
	else if(Edit == &edHieuChinhTheLoai) Edit = &edHieuChinhNXB;


	if(Edit == &edThemTenDocGia) Edit = &edThemHoDocGia;
	else if(Edit == &edThemPhaiDocGia) Edit = &edThemTenDocGia;
	else if(Edit == &edThemTrangThaiTheDocGia) Edit = &edThemPhaiDocGia;
	

	if(Edit == &edHieuChinhTenDocGia) Edit = &edHieuChinhHoDocGia;
	else if(Edit == &edHieuChinhPhaiDocGia) Edit = &edHieuChinhTenDocGia;
	else if(Edit == &edHieuChinhTrangThaiTheDocGia) Edit = &edHieuChinhPhaiDocGia;
}

void Scan(EditText* &txt, int maxn, ScanType type, int startLimit, int endLimit){
	if(txt == NULL) return;
	int mx = -1, my = -1, mrx = -1, mry = -1;
	int n = strlen(txt->content);

	getmouseclick(WM_LBUTTONDOWN, mx, my);
	clearmouseclick(WM_LBUTTONDOWN);
	
	getmouseclick(WM_RBUTTONDOWN, mrx, mry);
	clearmouseclick(WM_RBUTTONDOWN);
				
	if(((mx != -1 && my != -1) || (mrx != -1 && mry != -1)) && (!txt->isMouseHover(mx, my))){
		txt->content[n] = '\0';
		txt->draw();
		txt = NULL;
		return;
	}
		
	if(kbhit()){
		char c = getch();
		if(c == BACKSPACE && type != FIND_DS){
			if(n > 0){
				txt->content[n--] = ' ';
				txt->content[n] = ' ';
			}
		}else if(c == ENTER){
			txt->draw();
			txt->content[n] = '\0';

			MoveToNextEditText();
			
			return;
		}else if(n < maxn){

			if(type == ONLY_NUMBER){
				ScanNumber(txt, n, c);
			}else if(type == ONLY_NUMBER_GREATER_0){
				ScanNumberGreater0(txt, n, c);
			}else if(type == ONLY_TEXT){
				ScanTextOnly(txt, n, c);
			}else if(type == SPACE_TEXT){
				ScanTextSpace(txt, n, c);
			}else if(type == TEXT_NUMBER){
				ScanTextNumber(txt, n, c);
			}else if(type == DATE_TIME){
				ScanDate(txt, n, c);
			}else if(type == LIMIT_CHARACTER){
				ScanLimit(txt, n, c, startLimit, endLimit);
			}else if(type == ISBN){
				ScanNumber(txt, n, c);
				ScanTextOnly(txt, n, c);
			}else if(type == MASACH){
				ScanMaSach(txt, n, c);
			}
		}
		if(type == FIND_DS) ScanTimDauSach(txt, n, maxn, c);
		
		txt->content[n] = '_';
		txt->draw();
		txt->content[n] = '\0';
	}
}

void ScanLimit(EditText* &txt, int &n, char c, int start, int end){
	if(c >= start && c <= end){
		txt->content[n++] = c;
	}
}

void ScanDate(EditText* &txt, int &n, char c){
	int cnt = 0;
	for(int i=0; i<n; i++){
		if(txt->content[i] == '/') cnt++;
	}
	
	if(c >= '0' && c <= '9'){
		txt->content[n++] = c;
	}else if(c == '/' && cnt < 2 && n> 0 && txt->content[n-1] != '/'){
		txt->content[n++] = c;
	}
}

void ScanNumber(EditText* &txt, int &n, char c){
	if(c >= '0' && c <= '9'){
		txt->content[n++] = c;
	}
}
void ScanMaSach(EditText* &txt, int &n, char c)
{
	if(c >= '0' && c <= '9'){
		txt->content[n++] = c;
	}
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
		txt->content[n++] = toupper(c);
	}
	if(c == '-'){
		txt->content[n++] = c;
	}
}

void ScanNumberGreater0(EditText* &txt, int &n, char c){
	if(c >= '0' && c <= '9'){
		if(n == 0 && c == '0') return;
		txt->content[n++] = c;
	}
}

void ScanTextOnly(EditText* &txt, int &n, char c){
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
		txt->content[n++] = toupper(c);
	}
}

void ScanTextSpace(EditText* &txt, int &n, char c){
	if(c == SPACE){
		if(n > 0 && txt->content[n-1] != ' ')
			txt->content[n++] = ' ';
	}else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
		txt->content[n++] = toupper(c);
	}
}

void ScanTextNumber(EditText* &txt, int &n, char c){

	if(c == SPACE){
		if(n > 0 && txt->content[n-1] != ' ')
			txt->content[n++] = ' ';
	}else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
		txt->content[n++] = toupper(c);
	}else if(c >= '0' && c <= '9'){
		txt->content[n++] = c;
	}else if(c == ','){
		txt->content[n++] = c;
	}
}

void ScanTimDauSach(EditText* &txt, int &n, int maxn, char c){
	if(c == BACKSPACE){
		if(n > 0){
			txt->content[n--] = ' ';
			txt->content[n] = ' ';
		}
	}
	if(n < maxn){
		if(c == SPACE){
			if(n > 0 && txt->content[n-1] != ' ')
				txt->content[n++] = ' ';
		}else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
			txt->content[n++] = toupper(c);
		}
	} 
	
	txt->content[n] = '\0';
	GetListNodes(DSDS, txt->content, sizeListIndexDauSachSearch);
	curPageDauSach = 1;
	DrawList();

}

int checkXYConfirm(int x, int y){
	if(x>742 && x<826 && y>440 && y<483 ) return 1;
	else if(x>900 && x<1000 && y>440 && y<483) return 2;
	else return -1;
}

int checkConfirm(){
	int x,y;
	if(ismouseclick(WM_LBUTTONDOWN)){
		getmouseclick(WM_LBUTTONDOWN,x,y);
		clearmouseclick(WM_LBUTTONDOWN);
		int check = checkXYConfirm(x,y) ;
		if(check== 1 ) return 1;
		else if (check== 2) return 2;
		else return 0;
	}
	return -1;
}

void rectBox(int x1, int y1, int x2, int y2, int pattern,int background){
	setbkcolor(background);
	setcolor(background);
	rectangle(x1,y1,x2,y2);
	setfillstyle(pattern,background);
	floodfill(x1+1,y1+1,background);
}

void outText(char s[], int x, int y,int font, int color,int background,int size){
	setbkcolor(background);
	setcolor(color);
	settextstyle(font,0,size);
	outtextxy(x,y,s);
}

bool confirm(char *s1, char *s2){
	isChoose = true;
	setlinestyle(1,0,2);
	setcolor(YELLOW);	
	rectangle(680,330-2,1080,540+2);
	rectBox(680,330,1080,540,1,7);
	rectangle(792-2,440-2,876+2,483+2);
	rectangle(950-2,440-2,1035+2,483+2);	
	rectBox(742,440,826,483,1,GREEN);
	rectBox(900,440,1000,483,1,RED);	
	outText(s1,750,360,1,15,7,1);
	outText(s2,750,400,1,15,7,1);
	outText("Co",765,450,1,15,GREEN,1);
	outText("Khong",910,450,1,15,RED,1);
	while(1){
		int i = checkConfirm();
		if(i == 1) {
			//isChoose = false;
			return true;
		}
		else if(i == 2) 
		{
		//	isChoose = false;
			return false;
		}
		else if(i == 0) {
			setcolor(RED);
			rectangle(680,330-2,1080,540+2);
		}
		delay(10);
	}
}

void ClearStream(){
	while(kbhit()){
		char c = getch();
	}
}



