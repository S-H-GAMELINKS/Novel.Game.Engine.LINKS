
#include "DxLib.h"
#include "DEF.h"

// ������`��̈ʒu
int DrawPointX = 0, DrawPointY = 0;

// �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^
int SP = 0, CP = 0;

//�L�����N�^�[�摜�Ǎ��ϐ�
int CHARACTER_LOAD[12], CHARACTER, CHARACTER_DUMMY;

//�w�i�摜�Ǎ��ϐ�
int BACKGROUND_LOAD[12], BACKGROUND;

//�w�i���y�Ǎ��ϐ�
int BACKGROUNDMUSIC_LOAD[12], BACKGROUNDMUSIC;

//���ʉ��ϐ�
int SOUNDEFFECT_LOAD[12], SOUNDEFFECT;

//�X�N���v�g�Ǎ��ϐ�
int ScriptFile;

//�X�N���v�g�p�Ǎ��z��
char String[GYOU][RETU];

//�^�C�g���֘A
int TITLE;
unsigned int Cr;

//�Q�[���I�[�o�[
int GAMEOVER;

//�I�����Ǎ��ϐ�
char ChoiceA[RETU], ChoiceB[RETU];
int Choice1, Choice2;

//�G���h�t���O
int EndFlag = 99;

//�Q�[�����j���[�ϐ�
int GAMEMENU_COUNT;

//���ǃX�L�b�v�ϐ�
int LINKS = 0;
int A = 0;
int B = 0;
int C = 0;
int D = 0;
int E = 0;
int F = 0;
int G = 0;
int H = 0;
int I = 0;
int J = 0;
int K = 0;
int L = 0;
int M = 0;
int N = 0;

//�o�b�N���O�ϐ�
int BACKLOG_HANDLE, BACKLOG[11], BACKLOG_BACKGROUND;
int LOG = 1, BACKLOG_COUNT = 1;
char *BACKLOG_DELETE;

//�Z�[�u�p�ϐ�
int SAVE, SAVE_CHOICE = 0;
int SaveFlag = 0;
int SAVESNAP1, SAVESNAP2, SAVESNAP3, SAVETITLE;
int SAVESNAP_HANDLE1 = 0, SAVESNAP_HANDLE2 = 0, SAVESNAP_HANDLE3 = 0, SAVESNAP_CHOICE = 0;
char *SAVE_DATA_DELETE;
char *SAVESNAP_CHOICE_DELETE;

//�X�L�b�v�E�I�[�g���[�h�p�ϐ�
int skip_auto = 0;
int SKIP_SPEED = 100;
int SKIP_SPEED_COUNT = 10;
int AUTO_SPEED = 100;
int AUTO_SPEED_COUNT = 10;

//��A�N�e�B�u�p�ϐ�
char WindowActive = TRUE;

// �P�������ꎞ�L���z��
char OneMojiBuf[3];

//�L�����N�^�[���z��
char CHARACTER_NAME[10];

//�����`�摬�x�p�ϐ�
int STRING_SPEED = 100;
int STRING_SPEED_COUNT = 10;

//�T�E���h�m�x�����ƃE�C���h�E���̐؂�ւ��ϐ�
int soundnovel_winownovel = 0;

//�L�[����
int Key[256];
int y = MENUY;
int SAVE_y = SAVE_Y;
int GAME_y = GAMEMENU_y;

//�ݒ�p�ϐ�
int BGM_VOL_COUNT = 10;
int SE_VOL_COUNT = 10;
int BGM_VOL = 100;
int SE_VOL = 100;
int Config = 0;

//�X�N���[���V���b�g�p�ϐ�
int SCREENSHOT_COUNT = 0;

//�Z�[�u�E���[�h�֘A
//�ʏ�Z�[�u�f�[�^
typedef struct {
	int ENDFLAG;    //ENDFLAG
	int SP;			//�s��
	int CP;			//�����ʒu
	int CHAR;		//�����G���
	int BG;			//�w�i�摜���
	int BGM;		//BGM���
	int SAVE_CHOICE;//�I������ʂł̃Z�[�u���
}SaveData_t;

//�N�C�b�N�Z�[�u�f�[�^
typedef struct {
	int ENDFLAG;    //ENDFLAG
	int SP;			//�s��
	int CP;			//�����ʒu
	int CHAR;		//�����G���
	int BG;			//�w�i�摜���
	int BGM;		//BGM���
	int SAVE_CHOICE;//�I������ʂł̃Z�[�u���
}QuickSaveData_t;

//���ǃX�L�b�v
typedef struct {
	int LINKS;		//���C�����[�g�̊��Ǐ��
	int A;			//A���[�g�̊��Ǐ��
	int B;			//B���[�g�̊��Ǐ��
	int C;			//C���[�g�̊��Ǐ��
	int D;			//D���[�g�̊��Ǐ��
	int E;			//E���[�g�̊��Ǐ��
	int F;			//F���[�g�̊��Ǐ��
	int G;			//G���[�g�̊��Ǐ��
	int H;			//H���[�g�̊��Ǐ��
	int I;			//I���[�g�̊��Ǐ��
	int J;			//J���[�g�̊��Ǐ��
	int K;			//K���[�g�̊��Ǐ��
	int L;			//L���[�g�̊��Ǐ��
	int M;			//M���[�g�̊��Ǐ��
	int N;			//N���[�g�̊��Ǐ��
}SkipData_t;

//�ݒ�f�[�^
typedef struct {
	int BGM_VOL;				//BGM���ʏ��
	int BGM_VOL_COUNT;			//BGM���ʃ��[�^�[���
	int SE_VOL;					//SE���ʏ��
	int SE_VOL_COUNT;			//SE���ʃ��[�^�[���
	int SKIP_SPEED;				//�X�L�b�v���x���
	int SKIP_SPEED_COUNT;		//�X�L�b�v���x���[�^�[���
	int AUTO_SPEED;				//�I�[�g���x���
	int AUTO_SPEED_COUNT;		//�I�[�g���x���[�^�[���
	int STRING_SPEED;			//������`�摬�x
	int STRING_SPEED_COUNT;		//������`�摬�x���[�^�[���
	int soundnovel_winownovel;	//�T�E���h�m�x�����ƃE�C���h�E���`��̏��
}ConfigData_t;

//�e�f�ރf�[�^�Ǎ��֐�
int MATERIAL_LOAD() {

	//�T�E���h�f�[�^�̓ǂݍ��݌`��
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);

	//�L�����N�^�[�摜�Ǎ�
	CHARACTER_LOAD[0] = LoadGraph("DATA/CHARACTER/CHAR01.png");
	CHARACTER_LOAD[1] = LoadGraph("DATA/CHARACTER/CHAR02.png");
	CHARACTER_LOAD[2] = LoadGraph("DATA/CHARACTER/CHAR03.png");
	CHARACTER_LOAD[3] = LoadGraph("DATA/CHARACTER/CHAR04.png");
	CHARACTER_LOAD[4] = LoadGraph("DATA/CHARACTER/CHAR05.png");
	CHARACTER_LOAD[5] = LoadGraph("DATA/CHARACTER/CHAR06.png");
	CHARACTER_LOAD[6] = LoadGraph("DATA/CHARACTER/CHAR07.png");
	CHARACTER_LOAD[7] = LoadGraph("DATA/CHARACTER/CHAR08.png");
	CHARACTER_LOAD[8] = LoadGraph("DATA/CHARACTER/CHAR09.png");
	CHARACTER_LOAD[9] = LoadGraph("DATA/CHARACTER/CHAR10.png");
	CHARACTER_LOAD[10] = LoadGraph("DATA/CHARACTER/CHAR11.png");
	CHARACTER_LOAD[11] = LoadGraph("DATA/CHARACTER/CHAR12.png");

	//�w�i�摜�Ǎ�
	BACKGROUND_LOAD[0] = LoadGraph("DATA/BACKGROUND/BG01.png");
	BACKGROUND_LOAD[1] = LoadGraph("DATA/BACKGROUND/BG02.png");
	BACKGROUND_LOAD[2] = LoadGraph("DATA/BACKGROUND/BG03.png");
	BACKGROUND_LOAD[3] = LoadGraph("DATA/BACKGROUND/BG04.png");
	BACKGROUND_LOAD[4] = LoadGraph("DATA/BACKGROUND/BG05.png");
	BACKGROUND_LOAD[5] = LoadGraph("DATA/BACKGROUND/BG06.png");
	BACKGROUND_LOAD[6] = LoadGraph("DATA/BACKGROUND/BG07.png");
	BACKGROUND_LOAD[7] = LoadGraph("DATA/BACKGROUND/BG08.png");
	BACKGROUND_LOAD[8] = LoadGraph("DATA/BACKGROUND/BG09.png");
	BACKGROUND_LOAD[9] = LoadGraph("DATA/BACKGROUND/BG10.png");
	BACKGROUND_LOAD[10] = LoadGraph("DATA/BACKGROUND/BG11.png");
	BACKGROUND_LOAD[11] = LoadGraph("DATA/BACKGROUND/BG12.png");

	//�a�f�l�Ǎ�
	BACKGROUNDMUSIC_LOAD[0] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM01.ogg");
	BACKGROUNDMUSIC_LOAD[1] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM02.ogg");
	BACKGROUNDMUSIC_LOAD[2] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM03.ogg");
	BACKGROUNDMUSIC_LOAD[3] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM04.ogg");
	BACKGROUNDMUSIC_LOAD[4] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM05.ogg");
	BACKGROUNDMUSIC_LOAD[5] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM06.ogg");
	BACKGROUNDMUSIC_LOAD[6] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM07.ogg");
	BACKGROUNDMUSIC_LOAD[7] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM08.ogg");
	BACKGROUNDMUSIC_LOAD[8] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM09.ogg");
	BACKGROUNDMUSIC_LOAD[9] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM10.ogg");
	BACKGROUNDMUSIC_LOAD[10] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM11.ogg");
	BACKGROUNDMUSIC_LOAD[11] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM12.ogg");

	//�r�d�Ǎ�
	SOUNDEFFECT_LOAD[0] = LoadSoundMem("DATA/SOUNDEFFECT/SE01.ogg");
	SOUNDEFFECT_LOAD[1] = LoadSoundMem("DATA/SOUNDEFFECT/SE02.ogg");
	SOUNDEFFECT_LOAD[2] = LoadSoundMem("DATA/SOUNDEFFECT/SE03.ogg");
	SOUNDEFFECT_LOAD[3] = LoadSoundMem("DATA/SOUNDEFFECT/SE04.ogg");
	SOUNDEFFECT_LOAD[4] = LoadSoundMem("DATA/SOUNDEFFECT/SE05.ogg");
	SOUNDEFFECT_LOAD[5] = LoadSoundMem("DATA/SOUNDEFFECT/SE06.ogg");
	SOUNDEFFECT_LOAD[6] = LoadSoundMem("DATA/SOUNDEFFECT/SE07.ogg");
	SOUNDEFFECT_LOAD[7] = LoadSoundMem("DATA/SOUNDEFFECT/SE08.ogg");
	SOUNDEFFECT_LOAD[8] = LoadSoundMem("DATA/SOUNDEFFECT/SE09.ogg");
	SOUNDEFFECT_LOAD[9] = LoadSoundMem("DATA/SOUNDEFFECT/SE10.ogg");
	SOUNDEFFECT_LOAD[10] = LoadSoundMem("DATA/SOUNDEFFECT/SE11.ogg");
	SOUNDEFFECT_LOAD[11] = LoadSoundMem("DATA/SOUNDEFFECT/SE12.ogg");

	//�Q�[���I�[�o�[���
	GAMEOVER = LoadGraph("DATA/BACKGROUND/GAMEOVER.png");

	// ���F�̒l���擾
	Cr = GetColor(255, 255, 255);

	//�^�C�g�����j���[�w�i�摜�Ǎ�
	TITLE = LoadGraph("DATA/BACKGROUND/TITLE.png");

	return 0;
}

//�X�N���v�g�Ǎ��֐�
int SCRIPT_READ() {

	//���C�����[�g
	if (EndFlag == 1) {
		// ���C���X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/LINKS.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//A���[�g
	if (EndFlag == 2) {
		//A���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/A.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//B���[�g
	if (EndFlag == 3) {
		//�a���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/B.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//C���[�g
	if (EndFlag == 4) {
		//C���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/C.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//D���[�g
	if (EndFlag == 5) {
		//D���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/D.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//E���[�g
	if (EndFlag == 6) {
		//E���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/E.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//F���[�g
	if (EndFlag == 7) {
		//F���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/F.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//G���[�g
	if (EndFlag == 8) {
		//G���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/G.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//H���[�g
	if (EndFlag == 9) {
		//H���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/H.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//I���[�g
	if (EndFlag == 10) {
		//I���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/I.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//J���[�g
	if (EndFlag == 11) {
		//J���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/J.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//K���[�g
	if (EndFlag == 12) {
		//K���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/K.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//L���[�g
	if (EndFlag == 13) {
		//L���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/L.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//M���[�g
	if (EndFlag == 14) {
		//M���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/M.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	//N���[�g
	if (EndFlag == 15) {
		//N���[�g�̃X�N���v�g�t�@�C�����J��
		ScriptFile = FileRead_open("DATA/STR/N.txt");
		for (int i = 0; i < GYOU; i++) {
			FileRead_scanf(ScriptFile, "%s", String[i]);
		}
	}

	return 0;
}

//���L�[����֐�
int MoveKey(int KeyStateBuf[]) {

	//�L�[���͗p�ϐ�
	char GetHitKeyStateAll_Key[256];
	
	//�L�[�̏���ϐ���
	GetHitKeyStateAll(GetHitKeyStateAll_Key);
	
	//�L�[���͂̏�
	for (int i = 0; i<256; i++) {
	
		if (GetHitKeyStateAll_Key[i] == 1) KeyStateBuf[i]++;
		else                            KeyStateBuf[i] = 0;
	}
	return 0;
}

//�^�C�g�����j���[�J�[�\���֐�
void title(int Cr, int y) {

	//�J�[�\��
	DrawString(MENUX, y, "��", Cr);

	//�e���j���[����
	DrawString(MENUX + CURSOR, GAMESTART, "START", Cr);
	DrawString(MENUX + CURSOR, GAMELOAD, "LOAD", Cr);
	DrawString(MENUX + CURSOR, GAMECONFIG, "CONFIG", Cr);
	DrawString(MENUX + CURSOR, QUICKLOAD, "QUICKLOAD", Cr);
	DrawString(MENUX + CURSOR, GAMEQUIT, "QUIT", Cr);
}

//�Z�[�u���[�h���j���[�J�[�\���֐�
void SAVE_LOAD_MENU(int Cr, int SAVE_y) {
	DrawString(SAVE_X, SAVE_y, "��", Cr);
}

//�Q�[�����j���[�J�[�\���֐�
void GAME_MENU_CURSOR(int Cr, int GAME_y) {
	DrawString(SAVE_X - (CURSOR * 6), GAME_y, "��", Cr);
}

//�}�E�X����
int Mouse_Move() {

	//�}�E�X�̈ʒu���ϐ�
	int MouseX, MouseY;

	//�}�E�X�̈ʒu���擾
	GetMousePoint(&MouseX, &MouseY);

	//�^�C�g�����j���[
	if (EndFlag == 99) {

		if (MouseY <= 359)
			y = 330;

		if (MouseY >= 360 && MouseY <= 389)
			y = 360;

		if (MouseY >= 390 && MouseY <= 419)
			y = 390;

		if (MouseY >= 420 && MouseY <= 449)
			y = 420;

		if (MouseY >= 450)
			y = 450;

	}

	//�Q�[�����j���[
	if (EndFlag != 99 && GAMEMENU_COUNT == 0 && Config == 0) {

		if (MouseY <= 59)
			GAME_y = 30;

		if (MouseY >= 60 && MouseY <= 89)
			GAME_y = 60;

		if (MouseY >= 90 && MouseY <= 119)
			GAME_y = 90;

		if (MouseY >= 120 && MouseY <= 149)
			GAME_y = 120;

		if (MouseY >= 150 && MouseY <= 179)
			GAME_y = 150;

		if (MouseY >= 180 && MouseY <= 209)
			GAME_y = 180;

		if (MouseY >= 210 && MouseY <= 239)
			GAME_y = 210;

		if (MouseY >= 240 && MouseY <= 269)
			GAME_y = 240;

		if (MouseY >= 270 && MouseY <= 299)
			GAME_y = 270;

		if (MouseY >= 300 && MouseY <= 329)
			GAME_y = 300;

		if (MouseY >= 330 && MouseY <= 359)
			GAME_y = 330;

		if (MouseY >= 360)
			GAME_y = 360;
	}
	
	//�Z�[�u���
	if (EndFlag != 99 && GAMEMENU_COUNT == 0 && SaveFlag != 0) {

		if (MouseY <= 199)
			SAVE_y = 100;

		if (MouseY >= 200 && MouseY <= 299)
			SAVE_y = 200;

		if (MouseY >= 300 && MouseY <= 399)
			SAVE_y = 300;

		if (MouseY >= 400)
			SAVE_y = 400;

	}

	//�Z�[�u���(�^�C�g�����j���[)
	if (EndFlag == 99 && SaveFlag != 0) {

		if (MouseY <= 199)
			SAVE_y = 100;

		if (MouseY >= 200 && MouseY <= 299)
			SAVE_y = 200;

		if (MouseY >= 300 && MouseY <= 399)
			SAVE_y = 300;

		if (MouseY >= 400)
			SAVE_y = 400;

	}

	//�I�������
	if (EndFlag == 1 || EndFlag == 2 || EndFlag == 3 || EndFlag == 4 || EndFlag == 5 || EndFlag == 6 || EndFlag == 7) {

			if (MouseY <= 229)
				y = 200;

			if (MouseY >= 230)
				y = 230;
	}

	//�R���t�B�O���(�Q�[�����j���[)
	if (EndFlag != 99 && GAMEMENU_COUNT == 0 && Config == 1) {

		if (MouseY <= 59)
			GAME_y = 30;

		if (MouseY >= 60 && MouseY <= 89)
			GAME_y = 60;

		if (MouseY >= 90 && MouseY <= 119)
			GAME_y = 90;

		if (MouseY >= 120 && MouseY <= 149)
			GAME_y = 120;

		if (MouseY >= 150 && MouseY <= 179)
			GAME_y = 150;

		if (MouseY >= 180 && MouseY <= 209)
			GAME_y = 180;

		if (MouseY >= 210 && MouseY <= 239)
			GAME_y = 210;

		if (MouseY >= 240)
			GAME_y = 240;
	}

	//�R���t�B�O���(�^�C�g�����j���[)
	if (EndFlag == 99 && Config == 1) {

		if (MouseY <= 59)
			GAME_y = 30;

		if (MouseY >= 60 && MouseY <= 89)
			GAME_y = 60;

		if (MouseY >= 90 && MouseY <= 119)
			GAME_y = 90;

		if (MouseY >= 120 && MouseY <= 149)
			GAME_y = 120;

		if (MouseY >= 150 && MouseY <= 179)
			GAME_y = 150;

		if (MouseY >= 180 && MouseY <= 209)
			GAME_y = 180;

		if (MouseY >= 210 && MouseY <= 239)
			GAME_y = 210;

		if (MouseY >= 240)
			GAME_y = 240;
	}

	return 0;

}

//�Z�[�u�f�[�^���[�h�֐�(�^�C�g�����j���[)
int SAVEDATA_LOAD() {

	//�Z�[�u�f�[�^�E���[�h���
	if (SaveFlag == 2) {

		WaitTimer(600);

		//�Z�[�u���̃X�N���[���V���b�g�Ǎ�
		SAVESNAP1 = LoadGraph("DATA/SAVE/SAVESNAP1.png");
		SAVESNAP2 = LoadGraph("DATA/SAVE/SAVESNAP2.png");
		SAVESNAP3 = LoadGraph("DATA/SAVE/SAVESNAP3.png");
		SAVETITLE = LoadGraph("DATA/BACKGROUND/SAVE.png");

		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && SaveFlag == 2) {

			//�w�i�`��
			DrawGraph(0, 0, SAVETITLE, TRUE);

			//�J�[�\��
			SAVE_LOAD_MENU(Cr, SAVE_y);

			//�X�N���[���V���b�g�`��
			DrawRotaGraph(SAVE_SNAP_X, SAVE_Y, 0.2f, 0, SAVESNAP1, TRUE);
			DrawRotaGraph(SAVE_SNAP_X, SAVE_Y + SAVE_Y, 0.2f, 0, SAVESNAP2, TRUE);
			DrawRotaGraph(SAVE_SNAP_X, SAVE_Y + SAVE_Y + SAVE_Y, 0.2f, 0, SAVESNAP3, TRUE);

			//�Z�[�u�f�[�^���`��
			DrawString(SAVE_NAME_X, SAVE_Y, "�Z�[�u�f�[�^1", Cr);
			DrawString(SAVE_NAME_X, SAVE_Y + SAVE_Y, "�Z�[�u�f�[�^2", Cr);
			DrawString(SAVE_NAME_X, SAVE_Y + SAVE_Y + SAVE_Y, "�Z�[�u�f�[�^3", Cr);
			DrawString(SAVE_NAME_X - CURSOR, SAVE_Y + SAVE_Y + SAVE_Y + SAVE_Y, "�^�C�g���֖߂�", Cr);

			//�}�E�X����
			Mouse_Move();

			//�L�[����֘A
			SetDrawScreen(DX_SCREEN_BACK);

			ClearDrawScreen();

			if (Key[KEY_INPUT_DOWN] == 1) {
				ClearDrawScreen();
				SAVE_y += SAVE_MOVE;
				if (SAVE_y == (SAVE_Y_MAX + SAVE_MOVE + SAVE_MOVE))
					SAVE_y = SAVE_MOVE;
			}

			if (Key[KEY_INPUT_UP] == 1) {
				ClearDrawScreen();
				SAVE_y -= SAVE_MOVE;
				if (SAVE_y == (SAVE_Y - SAVE_MOVE))
					SAVE_y = SAVE_Y_MAX + SAVE_MOVE;
			}

			SetDrawScreen(DX_SCREEN_FRONT);

			//�Z�[�u�f�[�^�P�̃��[�h
			if (SAVE_y == SAVE_Y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == SAVE_Y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�Z�[�u�f�[�^1�����[�h���܂����H",
					"�m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {
					SaveData_t Data;
#pragma warning(disable:4996);
					FILE *fp = fopen("DATA/SAVE/SAVEDATA1.dat", "rb");
					if (fp == NULL) {

						MessageBox(
							NULL,
							"�Z�[�u�f�[�^1������܂���I",
							"�m�x���Q�[���G���W���uLINKS�v",
							MB_OK
						);

						return 0;
					}
					fread(&Data, sizeof(Data), 1, fp);
					EndFlag = Data.ENDFLAG;
					SP = Data.SP;
					CP = Data.CP;
					CHARACTER = Data.CHAR;
					BACKGROUND = Data.BG;
					BACKGROUNDMUSIC = Data.BGM;
					SAVE_CHOICE = Data.SAVE_CHOICE;

					//�T�E���h�m�x�����`��̏���
					if (soundnovel_winownovel == 0) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 0;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						MessageBox(
							NULL,
							"���[�h���܂����I",
							"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
							MB_OK
						);

						WaitTimer(300);

					}

					//�E�C���h�E���`�掞�̏���
					if (soundnovel_winownovel == 1) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						int	Window_Color = GetColor(0, 0, 0);

						DrawBox(0, 400, 640, 480, Window_Color, TRUE);

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 400;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						MessageBox(
							NULL,
							"���[�h���܂����I",
							"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
							MB_OK
						);

						WaitTimer(300);

					}

					fclose(fp);
					break;
				}
			}

			//�Z�[�u�f�[�^�Q�̃��[�h
			if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�Z�[�u�f�[�^2�����[�h���܂����H",
					"�m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {
					SaveData_t Data;
#pragma warning(disable:4996);
					FILE *fp = fopen("DATA/SAVE/SAVEDATA2.dat", "rb");
					if (fp == NULL) {

						MessageBox(
							NULL,
							"�Z�[�u�f�[�^2������܂���I",
							"�m�x���Q�[���G���W���uLINKS�v",
							MB_OK
						);

						return 0;
					}
					fread(&Data, sizeof(Data), 1, fp);
					EndFlag = Data.ENDFLAG;
					SP = Data.SP;
					CP = Data.CP;
					CHARACTER = Data.CHAR;
					BACKGROUND = Data.BG;
					BACKGROUNDMUSIC = Data.BGM;
					SAVE_CHOICE = Data.SAVE_CHOICE;

					//�T�E���h�m�x�����`��̏���
					if (soundnovel_winownovel == 0) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 0;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						MessageBox(
							NULL,
							"���[�h���܂����I",
							"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
							MB_OK
						);

						WaitTimer(300);

					}

					//�E�C���h�E���`�掞�̏���
					if (soundnovel_winownovel == 1) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						int	Window_Color = GetColor(0, 0, 0);

						DrawBox(0, 400, 640, 480, Window_Color, TRUE);

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 400;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						MessageBox(
							NULL,
							"���[�h���܂����I",
							"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
							MB_OK
						);

						WaitTimer(300);

					}

					fclose(fp);
					break;
				}
			}

			//�Z�[�u�f�[�^�R�̃��[�h
			if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�Z�[�u�f�[�^3�����[�h���܂����H",
					"�m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {
					SaveData_t Data;
#pragma warning(disable:4996);
					FILE *fp = fopen("DATA/SAVE/SAVEDATA3.dat", "rb");
					if (fp == NULL) {

						MessageBox(
							NULL,
							"�Z�[�u�f�[�^3������܂���I",
							"�m�x���Q�[���G���W���uLINKS�v",
							MB_OK
						);

						return 0;
					}
					fread(&Data, sizeof(Data), 1, fp);
					EndFlag = Data.ENDFLAG;
					SP = Data.SP;
					CP = Data.CP;
					CHARACTER = Data.CHAR;
					BACKGROUND = Data.BG;
					BACKGROUNDMUSIC = Data.BGM;
					SAVE_CHOICE = Data.SAVE_CHOICE;

					//�T�E���h�m�x�����`��̏���
					if (soundnovel_winownovel == 0) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 0;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						MessageBox(
							NULL,
							"���[�h���܂����I",
							"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
							MB_OK
						);

						WaitTimer(300);

					}

					//�E�C���h�E���`�掞�̏���
					if (soundnovel_winownovel == 1) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						int	Window_Color = GetColor(0, 0, 0);

						DrawBox(0, 400, 640, 480, Window_Color, TRUE);

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 400;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						MessageBox(
							NULL,
							"���[�h���܂����I",
							"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
							MB_OK
						);

						WaitTimer(300);

					}

					fclose(fp);
					break;
				}
			}

			//�^�C�g���ɖ߂�
			if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
				
				SAVE = MessageBox(
					NULL,
					"�^�C�g���ɖ߂�܂����H",
					"�m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {
					EndFlag = 99;
					SaveFlag = 0;
					WaitTimer(600);
					break;
				}
			}

		}
	}

	return 0;
}

//SKIP_READ LOAD�֐�
int SKIP_READ_LOAD()
{
	//���ǃf�[�^��ǂݍ���ŁA�e�ϐ��ɑ��
	SkipData_t Data;
#pragma warning(disable:4996);
	FILE *fp = fopen("DATA/SAVE/SKIP_READ.dat", "rb");
	if (fp == NULL) {
		return 0;
	}
	fread(&Data, sizeof(Data), 1, fp);
	LINKS = Data.LINKS;
	A = Data.A;
	B = Data.B;
	C = Data.C;
	D = Data.D;
	E = Data.E;
	F = Data.F;
	G = Data.G;
	H = Data.H;
	I = Data.I;
	J = Data.J;
	K = Data.K;
	L = Data.L;
	M = Data.M;
	N = Data.N;

}

//SKIP_READ SAVE�֐�
int SKIP_READ_SAVE()
{
		//���ǃX�L�b�v�f�[�^�ۑ�
#pragma warning(disable:4996);
		SkipData_t Data = { LINKS, A, B, C, D, E, F, G, H, I, J, K, L, M, N };
		FILE *fp = fopen("DATA/SAVE/SKIP_READ.dat", "wb");//�o�C�i���t�@�C�����J��
		if (fp == NULL) {//�G���[���N������NULL��Ԃ�
			return 0;
		}
		fwrite(&Data, sizeof(Data), 1, fp); // SkipData_t�\���̂̒��g���o��
		fclose(fp);//�t�@�C�������

	return 0;

}

//CONFIG_SAVE�֐�
int CONFIG_SAVE()
{
	//�ݒ�f�[�^�ۑ�
	#pragma warning(disable:4996);
	ConfigData_t Data = { BGM_VOL, BGM_VOL_COUNT, SE_VOL, SE_VOL_COUNT, SKIP_SPEED, SKIP_SPEED_COUNT, AUTO_SPEED, AUTO_SPEED_COUNT, STRING_SPEED, STRING_SPEED_COUNT, soundnovel_winownovel };
	FILE *fp = fopen("DATA/SAVE/Config.dat", "wb");//�o�C�i���t�@�C�����J��
	if (fp == NULL) {//�G���[���N������NULL��Ԃ�
		return 0;
	}
	fwrite(&Data, sizeof(Data), 1, fp); // ConfigData_t�\���̂̒��g���o��
	fclose(fp);//�t�@�C�������

	return 0;

}

//CONFIG_LOAD�֐�
int CONFIG_LOAD()
{
	//�ݒ�f�[�^�̓ǂݍ���
	ConfigData_t Data;
	#pragma warning(disable:4996);
	FILE *fp = fopen("DATA/SAVE/Config.dat", "rb");
	if (fp == NULL) {
		return 0;
	}
	fread(&Data, sizeof(Data), 1, fp);

	//�e��ϐ��ɑ��
	BGM_VOL = Data.BGM_VOL;
	BGM_VOL_COUNT = Data.BGM_VOL_COUNT;
	SE_VOL = Data.SE_VOL;
	SE_VOL_COUNT = Data.SE_VOL_COUNT;
	SKIP_SPEED = Data.SKIP_SPEED;
	SKIP_SPEED_COUNT = Data.SKIP_SPEED_COUNT;
	AUTO_SPEED = Data.AUTO_SPEED;
	AUTO_SPEED_COUNT = Data.AUTO_SPEED_COUNT;
	STRING_SPEED = Data.STRING_SPEED;
	STRING_SPEED_COUNT = Data.STRING_SPEED_COUNT;
	soundnovel_winownovel = Data.soundnovel_winownovel;

	return 0;

}

//�N�C�b�N�Z�[�u
int QUICKSAVE_SAVE(){

	//�N�C�b�N�Z�[�u�f�[�^�̍쐬 
#pragma warning(disable:4996);
	QuickSaveData_t Data = { EndFlag, SP, 0, CHARACTER, BACKGROUND, BACKGROUNDMUSIC, SAVE_CHOICE };
	FILE *fp = fopen("DATA/SAVE/QUICKSAVEDATA.dat", "wb");//�o�C�i���t�@�C�����J��
	if (fp == NULL) {//�G���[���N������NULL��Ԃ�
		return 0;
	}
	fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t�\���̂̒��g���o��
	fclose(fp);//�t�@�C�������

	return 0;

}

//�N�C�b�N���[�h
int QUICKSAVE_LOAD() {

	//�N�C�b�N�Z�[�u�f�[�^�̓ǂݍ���
	QuickSaveData_t Data;
#pragma warning(disable:4996);
	FILE *fp = fopen("DATA/SAVE/QUICKSAVEDATA.dat", "rb");
	if (fp == NULL) {
		return 0;
	}
	fread(&Data, sizeof(Data), 1, fp);
	EndFlag = Data.ENDFLAG;
	SP = Data.SP;
	CP = Data.CP;
	CHARACTER = Data.CHAR;
	BACKGROUND = Data.BG;
	BACKGROUNDMUSIC = Data.BGM;
	SAVE_CHOICE = Data.SAVE_CHOICE;

	//�T�E���h�m�x�����`��̏���
	if (soundnovel_winownovel == 0) {

		ClearDrawScreen();
		GAMEMENU_COUNT = 1;

		//�w�i�̕\��
		if (BACKGROUND != 0) {
			DrawGraph(0, 0, BACKGROUND, TRUE);
		}

		//�����G�̕\��
		if (CHARACTER != 0) {
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
		}

		//�a�f�l�̍Đ�
		if (BACKGROUNDMUSIC != 0) {

			// ���ʂ̐ݒ�
			ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

			PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		}

		DrawPointY = 0;
		DrawPointX = 0;

		if (SP != 0) {
			SP = SP - 1;
			CP = EOF;
		}

		if (SP == 0) {
			SP = 0;
			CP = 0;
		}

		MessageBox(
			NULL,
			"���[�h���܂����I",
			"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
			MB_OK
		);

		WaitTimer(300);
	}

	//�E�C���h�E���`�掞�̏���
	if (soundnovel_winownovel == 1) {

		ClearDrawScreen();
		GAMEMENU_COUNT = 1;

		//�w�i�̕\��
		if (BACKGROUND != 0) {
			DrawGraph(0, 0, BACKGROUND, TRUE);
		}

		int	Window_Color = GetColor(0, 0, 0);

		DrawBox(0, 400, 640, 480, Window_Color, TRUE);

		//�����G�̕\��
		if (CHARACTER != 0) {
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
		}

		//�a�f�l�̍Đ�
		if (BACKGROUNDMUSIC != 0) {

			// ���ʂ̐ݒ�
			ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

			PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		}

		DrawPointY = 400;
		DrawPointX = 0;

		if (SP != 0) {
			SP = SP - 1;
			CP = EOF;
		}

		if (SP == 0) {
			SP = 0;
			CP = 0;
		}

		MessageBox(
			NULL,
			"���[�h���܂����I",
			"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
			MB_OK
		);

		WaitTimer(300);
	}

	fclose(fp);

	return 0;

}

//�Z�[�u�E���[�h�E�X�L�b�v�E�I�[�g�� �Q�[�����j���[
int GAMEMENU() {

	//�Q�[�����j���[���J��
	if (CheckHitKey(KEY_INPUT_BACK) == 1 || (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {

		GAMEMENU_COUNT = 0;
		ClearDrawScreen();
		StopSoundMem(BACKGROUNDMUSIC);
		GAME_y = GAMEMENU_y;

		WaitTimer(300);

		//�Q�[�����j���[���[�v
		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && GAMEMENU_COUNT == 0) {

			//�e���j���[�`��
			DrawString(SAVE_NAME_X, GAMEMENU_y, "�Z�[�u", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 2, "���[�h", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 3, "�Z�[�u�f�[�^�폜", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 4, "���ǃX�L�b�v", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 5, "�X�L�b�v", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 6, "�I�[�g", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 7, "�I�[�g/�X�L�b�v��~", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 8, "�o�b�N���O�Q��", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 9, "�ݒ�", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 10, "�^�C�g���ɖ߂�", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 11, "�Q�[���ɖ߂�", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 12, "�Q�[���I��", Cr);

			//�L�[����֘A
			SetDrawScreen(DX_SCREEN_BACK);

			ClearDrawScreen();

			//�J�[�\���`��
			GAME_MENU_CURSOR(Cr, GAME_y);

			//�}�E�X����
			Mouse_Move();

			if (Key[KEY_INPUT_DOWN] == 1) {
				ClearDrawScreen();
				GAME_y += GAMEMENU_y;
				if (GAME_y == (GAMEMENU_y * 13))
					GAME_y = GAMEMENU_y;
			}

			if (Key[KEY_INPUT_UP] == 1) {
				ClearDrawScreen();
				GAME_y -= GAMEMENU_y;
				if (GAME_y == (GAMEMENU_y - GAMEMENU_y))
					GAME_y = (GAMEMENU_y * 12);
			}

			SetDrawScreen(DX_SCREEN_FRONT);

			//�Z�[�u
			if (GAME_y == GAMEMENU_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == GAMEMENU_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�Z�[�u��ʂɈڍs���܂����H",
					"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {
					ClearDrawScreen();
					SaveFlag = 1;
					SAVE_y = SAVE_Y;
				}

				WaitTimer(300);

				//�Z�[�u�f�[�^�E�Z�[�u���
				if (SaveFlag == 1) {

					//�Z�[�u���̃X�N���[���V���b�g�Ǎ�
					SAVESNAP1 = LoadGraph("DATA/SAVE/SAVESNAP1.png");
					SAVESNAP2 = LoadGraph("DATA/SAVE/SAVESNAP2.png");
					SAVESNAP3 = LoadGraph("DATA/SAVE/SAVESNAP3.png");
					SAVETITLE = LoadGraph("DATA/BACKGROUND/SAVE.png");

					WaitTimer(600);

					//�Z�[�u��ʃ��[�v
					while (ProcessMessage() == 0 && MoveKey(Key) == 0) {

						//�w�i�`��
						DrawGraph(0, 0, SAVETITLE, TRUE);

						//�J�[�\���`��
						SAVE_LOAD_MENU(Cr, SAVE_y);

						//�X�N���[���V���b�g�`��
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y, 0.2f, 0, SAVESNAP1, TRUE);
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 2, 0.2f, 0, SAVESNAP2, TRUE);
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 3, 0.2f, 0, SAVESNAP3, TRUE);

						//�Z�[�u�f�[�^���`��
						DrawString(SAVE_NAME_X, SAVE_Y, "�Z�[�u�f�[�^1", Cr);
						DrawString(SAVE_NAME_X, SAVE_Y * 2, "�Z�[�u�f�[�^2", Cr);
						DrawString(SAVE_NAME_X, SAVE_Y * 3, "�Z�[�u�f�[�^3", Cr);
						DrawString(SAVE_NAME_X - CURSOR, SAVE_Y * 4, "���j���[�ɖ߂�", Cr);

						//�L�[����֘A
						SetDrawScreen(DX_SCREEN_BACK);

						ClearDrawScreen();

						//�}�E�X����
						Mouse_Move();

						if (Key[KEY_INPUT_DOWN] == 1) {
							ClearDrawScreen();
							SAVE_y += SAVE_MOVE;
							if (SAVE_y == (SAVE_Y_MAX + SAVE_MOVE + SAVE_MOVE))
								SAVE_y = SAVE_MOVE;
						}

						if (Key[KEY_INPUT_UP] == 1) {
							ClearDrawScreen();
							SAVE_y -= SAVE_MOVE;
							if (SAVE_y == (SAVE_Y - SAVE_MOVE))
								SAVE_y = SAVE_Y_MAX + SAVE_MOVE;
						}

						SetDrawScreen(DX_SCREEN_FRONT);

						//�Z�[�u�f�[�^�P�ɃZ�[�u
						if (SAVE_y == SAVE_Y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == SAVE_Y && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"�Z�[�u�f�[�^1�ɃZ�[�u���܂����H",
								"�m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								//�Z�[�u�f�[�^�P�p�̃X�N���[���V���b�g�擾�ϐ�
								SAVESNAP_HANDLE1 = 1;

								//�I������ʂł̃Z�[�u����
								if (SAVESNAP_CHOICE != 0) {

									SetDrawScreen(DX_SCREEN_BACK);

									DrawGraph(0, 0, SAVESNAP_CHOICE, TRUE);

									SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP1.png", 0);

									SAVESNAP_CHOICE = 0;

									SAVESNAP_HANDLE1 = 0;

									SetDrawScreen(DX_SCREEN_FRONT);

								}


								//�Z�[�u�f�[�^�̍쐬 
#pragma warning(disable:4996);
								SaveData_t Data = { EndFlag, SP, 0, CHARACTER, BACKGROUND, BACKGROUNDMUSIC, SAVE_CHOICE };
								FILE *fp = fopen("DATA/SAVE/SAVEDATA1.dat", "wb");//�o�C�i���t�@�C�����J��
								if (fp == NULL) {//�G���[���N������NULL��Ԃ�
									return 0;
								}
								fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t�\���̂̒��g���o��
								fclose(fp);//�t�@�C�������

								MessageBox(
									NULL,
									"�Z�[�u���܂����I",
									"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
									MB_OK
									);

								//�T�E���h�m�x�����`�掞�̏���
								if (soundnovel_winownovel == 0) {

									SaveFlag = 0;
									ClearDrawScreen();

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {
										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 0;
									DrawPointX = 0;

									if (SP != 0) {
										SP = SP - 1;
										CP = EOF;
									}

									if (SP == 0) {
										SP = 0;
										CP = 0;
									}

									SAVE_CHOICE = 0;

									GAMEMENU_COUNT = 1;

									break;
								}

								//�E�C���h�E���`�掞�̏���
								if (soundnovel_winownovel == 1) {

									SaveFlag = 0;
									ClearDrawScreen();

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									int	Window_Color = GetColor(0, 0, 0);

									DrawBox(0, 400, 640, 480, Window_Color, TRUE);

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {
										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 400;
									DrawPointX = 0;

									if (SP != 0) {
										SP = SP - 1;
										CP = EOF;
									}

									if (SP == 0) {
										SP = 0;
										CP = 0;
									}

									SAVE_CHOICE = 0;

									GAMEMENU_COUNT = 1;

									break;
								}

							}

							WaitTimer(300);
						}

						//�Z�[�u�f�[�^�Q�ɃZ�[�u
						if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"�Z�[�u�f�[�^2�ɃZ�[�u���܂����H",
								"�m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								SAVESNAP_HANDLE2 = 1;

								//�I������ʂł̃Z�[�u����
								if (SAVESNAP_CHOICE != 0) {

									SetDrawScreen(DX_SCREEN_BACK);

									DrawGraph(0, 0, SAVESNAP_CHOICE, TRUE);

									SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP2.png", 0);

									SAVESNAP_CHOICE = 0;

									SAVESNAP_HANDLE3 = 0;

									SetDrawScreen(DX_SCREEN_FRONT);

								}

								//�Z�[�u�f�[�^�̍쐬 
#pragma warning(disable:4996);
								SaveData_t Data = { EndFlag, SP, 0, CHARACTER, BACKGROUND, BACKGROUNDMUSIC, SAVE_CHOICE };
								FILE *fp = fopen("DATA/SAVE/SAVEDATA2.dat", "wb");//�o�C�i���t�@�C�����J��
								if (fp == NULL) {//�G���[���N������NULL��Ԃ�
									return 0;
								}
								fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t�\���̂̒��g���o��
								fclose(fp);//�t�@�C�������

								MessageBox(
									NULL,
									"�Z�[�u���܂����I",
									"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
									MB_OK
									);

								//�T�E���h�m�x�����`�掞�̏���
								if (soundnovel_winownovel == 0) {

									SaveFlag = 0;
									ClearDrawScreen();

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {
										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 0;
									DrawPointX = 0;

									if (SP != 0) {
										SP = SP - 1;
										CP = EOF;
									}

									if (SP == 0) {
										SP = 0;
										CP = 0;
									}

									SAVE_CHOICE = 0;

									GAMEMENU_COUNT = 1;

									break;
								}

								//�E�C���h�E���`�掞�̏���
								if (soundnovel_winownovel == 1) {

									SaveFlag = 0;
									ClearDrawScreen();

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									int	Window_Color = GetColor(0, 0, 0);

									DrawBox(0, 400, 640, 480, Window_Color, TRUE);

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {
										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 400;
									DrawPointX = 0;

									if (SP != 0) {
										SP = SP - 1;
										CP = EOF;
									}

									if (SP == 0) {
										SP = 0;
										CP = 0;
									}

									SAVE_CHOICE = 0;

									GAMEMENU_COUNT = 1;

									break;
								}
							}

							WaitTimer(300);
						}

						//�Z�[�u�f�[�^�R�ɃZ�[�u
						if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"�Z�[�u�f�[�^3�ɃZ�[�u���܂����H",
								"�m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								SAVESNAP_HANDLE3 = 1;

								//�I������ʂł̃Z�[�u����
								if (SAVESNAP_CHOICE != 0) {

									SetDrawScreen(DX_SCREEN_BACK);

									DrawGraph(0, 0, SAVESNAP_CHOICE, TRUE);

									SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP3.png", 0);

									SAVESNAP_CHOICE = 0;

									SAVESNAP_HANDLE3 = 0;

									SetDrawScreen(DX_SCREEN_FRONT);

								}

								//�Z�[�u�f�[�^�̍쐬 
#pragma warning(disable:4996);
								SaveData_t Data = { EndFlag, SP, 0, CHARACTER, BACKGROUND, BACKGROUNDMUSIC, SAVE_CHOICE };
								FILE *fp = fopen("DATA/SAVE/SAVEDATA3.dat", "wb");//�o�C�i���t�@�C�����J��
								if (fp == NULL) {//�G���[���N������NULL��Ԃ�
									return 0;
								}
								fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t�\���̂̒��g���o��
								fclose(fp);//�t�@�C�������

								MessageBox(
									NULL,
									"�Z�[�u���܂����I",
									"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
									MB_OK
									);

								//�T�E���h�m�x�����`�掞�̏���
								if (soundnovel_winownovel == 0) {

									SaveFlag = 0;
									ClearDrawScreen();

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {
										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 0;
									DrawPointX = 0;

									if (SP != 0) {
										SP = SP - 1;
										CP = EOF;
									}

									if (SP == 0) {
										SP = 0;
										CP = 0;
									}

									SAVE_CHOICE = 0;

									GAMEMENU_COUNT = 1;

									break;
								}

								//�E�C���h�E���`�掞�̏���
								if (soundnovel_winownovel == 1) {

									SaveFlag = 0;
									ClearDrawScreen();

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									int	Window_Color = GetColor(0, 0, 0);

									DrawBox(0, 400, 640, 480, Window_Color, TRUE);

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {
										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 400;
									DrawPointX = 0;

									if (SP != 0) {
										SP = SP - 1;
										CP = EOF;
									}

									if (SP == 0) {
										SP = 0;
										CP = 0;
									}

									SAVE_CHOICE = 0;

									GAMEMENU_COUNT = 1;

									break;
								}


							}

							WaitTimer(300);
						}

						//���j���[��ʂɖ߂�
						if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
							SAVE = MessageBox(
								NULL,
								"���j���[�ɖ߂�܂����H",
								"�m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								ClearDrawScreen();
								WaitTimer(300);

								break;
							}

							WaitTimer(300);
						}
					}

					WaitTimer(1800);
				}
			}

			//���[�h
			if (GAME_y == (GAMEMENU_y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 2) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {


				SAVE = MessageBox(
					NULL,
					"���[�h��ʂɈڍs���܂����H",
					"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					ClearDrawScreen();
					SaveFlag = 4;
					WaitTimer(600);

					SAVE_y = SAVE_Y;

					//�Z�[�u���̃X�N���[���V���b�g�Ǎ�
					SAVESNAP1 = LoadGraph("DATA/SAVE/SAVESNAP1.png");
					SAVESNAP2 = LoadGraph("DATA/SAVE/SAVESNAP2.png");
					SAVESNAP3 = LoadGraph("DATA/SAVE/SAVESNAP3.png");
					SAVETITLE = LoadGraph("DATA/BACKGROUND/SAVE.png");

					//���[�h��ʂ̃��[�v
					while (ProcessMessage() == 0 && MoveKey(Key) == 0) {

						//�w�i�`��
						DrawGraph(0, 0, SAVETITLE, TRUE);

						//�J�[�\���`��
						SAVE_LOAD_MENU(Cr, SAVE_y);

						//�X�N���[���V���b�g�`��
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y, 0.2f, 0, SAVESNAP1, TRUE);
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 2, 0.2f, 0, SAVESNAP2, TRUE);
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 3, 0.2f, 0, SAVESNAP3, TRUE);

						//�Z�[�u�f�[�^���`��
						DrawString(SAVE_NAME_X, SAVE_Y, "�Z�[�u�f�[�^1", Cr);
						DrawString(SAVE_NAME_X, SAVE_Y * 2, "�Z�[�u�f�[�^2", Cr);
						DrawString(SAVE_NAME_X, SAVE_Y * 3, "�Z�[�u�f�[�^3", Cr);
						DrawString(SAVE_NAME_X - CURSOR, SAVE_Y * 4, "���j���[�ɖ߂�", Cr);

						//�L�[����֘A
						SetDrawScreen(DX_SCREEN_BACK);

						ClearDrawScreen();

						//�}�E�X����
						Mouse_Move();

						if (Key[KEY_INPUT_DOWN] == 1) {
							ClearDrawScreen();
							SAVE_y += SAVE_MOVE;
							if (SAVE_y == (SAVE_Y_MAX + SAVE_MOVE + SAVE_MOVE))
								SAVE_y = SAVE_MOVE;
						}

						if (Key[KEY_INPUT_UP] == 1) {
							ClearDrawScreen();
							SAVE_y -= SAVE_MOVE;
							if (SAVE_y == (SAVE_Y - SAVE_MOVE))
								SAVE_y = SAVE_Y_MAX + SAVE_Y;
						}

						SetDrawScreen(DX_SCREEN_FRONT);

						//�Z�[�u�f�[�^�P�̃��[�h
						if (SAVE_y == SAVE_Y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == SAVE_Y && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"�Z�[�u�f�[�^1�����[�h���܂����H",
								"�m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								ClearDrawScreen();

								GAMEMENU_COUNT = 1;

								SaveData_t Data;
#pragma warning(disable:4996);
								FILE *fp = fopen("DATA/SAVE/SAVEDATA1.dat", "rb");
								if (fp == NULL) {

									MessageBox(
										NULL,
										"�Z�[�u�f�[�^1������܂���I",
										"�m�x���Q�[���G���W���uLINKS�v",
										MB_OK
									);
								}
								fread(&Data, sizeof(Data), 1, fp);
								EndFlag = Data.ENDFLAG;
								SP = Data.SP;
								CP = Data.CP;
								CHARACTER = Data.CHAR;
								BACKGROUND = Data.BG;
								BACKGROUNDMUSIC = Data.BGM;
								SAVE_CHOICE = Data.SAVE_CHOICE;

								//�T�E���h�m�x�����`��̏���
								if (soundnovel_winownovel == 0) {

									ClearDrawScreen();
									GAMEMENU_COUNT = 1;

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {

										// ���ʂ̐ݒ�
										ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 0;
									DrawPointX = 0;

									if (SP != 0) {
										SP = SP - 1;
										CP = EOF;
									}

									if (SP == 0) {
										SP = 0;
										CP = 0;
									}

									MessageBox(
										NULL,
										"���[�h���܂����I",
										"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
										MB_OK
									);

									WaitTimer(300);
								}

								//�E�C���h�E���`�掞�̏���
								if (soundnovel_winownovel == 1) {

									ClearDrawScreen();
									GAMEMENU_COUNT = 1;

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									int	Window_Color = GetColor(0, 0, 0);

									DrawBox(0, 400, 640, 480, Window_Color, TRUE);

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {

										// ���ʂ̐ݒ�
										ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 400;
									DrawPointX = 0;

									if (SP != 0) {
										SP = SP - 1;
										CP = EOF;
									}

									if (SP == 0) {
										SP = 0;
										CP = 0;
									}

									MessageBox(
										NULL,
										"���[�h���܂����I",
										"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
										MB_OK
									);


									WaitTimer(300);
								}

								break;
							}

							WaitTimer(300);
						}

						if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"�Z�[�u�f�[�^2�����[�h���܂����H",
								"�m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								ClearDrawScreen();

								GAMEMENU_COUNT = 1;

								SaveData_t Data;
#pragma warning(disable:4996);
								FILE *fp = fopen("DATA/SAVE/SAVEDATA2.dat", "rb");
								if (fp == NULL) {

									MessageBox(
										NULL,
										"�Z�[�u�f�[�^2������܂���I",
										"�m�x���Q�[���G���W���uLINKS�v",
										MB_OK
									);
								}
								fread(&Data, sizeof(Data), 1, fp);
								EndFlag = Data.ENDFLAG;
								SP = Data.SP;
								CP = Data.CP;
								CHARACTER = Data.CHAR;
								BACKGROUND = Data.BG;
								BACKGROUNDMUSIC = Data.BGM;
								SAVE_CHOICE = Data.SAVE_CHOICE;

								//�T�E���h�m�x�����`��̏���
								if (soundnovel_winownovel == 0) {

									ClearDrawScreen();
									GAMEMENU_COUNT = 1;

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {

										// ���ʂ̐ݒ�
										ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 0;
									DrawPointX = 0;

									if (SP != 0) {
										SP = SP - 1;
										CP = EOF;
									}

									if (SP == 0) {
										SP = 0;
										CP = 0;
									}

									MessageBox(
										NULL,
										"���[�h���܂����I",
										"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
										MB_OK
									);

									WaitTimer(300);
								}

								//�E�C���h�E���`�掞�̏���
								if (soundnovel_winownovel == 1) {

									ClearDrawScreen();
									GAMEMENU_COUNT = 1;

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									int	Window_Color = GetColor(0, 0, 0);

									DrawBox(0, 400, 640, 480, Window_Color, TRUE);

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {

										// ���ʂ̐ݒ�
										ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 400;
									DrawPointX = 0;

									if (SP != 0) {
										SP = SP - 1;
										CP = EOF;
									}

									if (SP == 0) {
										SP = 0;
										CP = 0;
									}

									MessageBox(
										NULL,
										"���[�h���܂����I",
										"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
										MB_OK
									);

									WaitTimer(300);
								}

								break;

							}

							WaitTimer(300);
						}

						//�Z�[�u�f�[�^�R�̃��[�h
						if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"�Z�[�u�f�[�^3�����[�h���܂����H",
								"�m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								ClearDrawScreen();

								GAMEMENU_COUNT = 1;

								SaveData_t Data;
#pragma warning(disable:4996);
								FILE *fp = fopen("DATA/SAVE/SAVEDATA3.dat", "rb");
								if (fp == NULL) {

									MessageBox(
										NULL,
										"�Z�[�u�f�[�^3������܂���I",
										"�m�x���Q�[���G���W���uLINKS�v",
										MB_OK
									);
								}
								fread(&Data, sizeof(Data), 1, fp);
								EndFlag = Data.ENDFLAG;
								SP = Data.SP;
								CP = Data.CP;
								CHARACTER = Data.CHAR;
								BACKGROUND = Data.BG;
								BACKGROUNDMUSIC = Data.BGM;
								SAVE_CHOICE = Data.SAVE_CHOICE;

								//�T�E���h�m�x�����`��̏���
								if (soundnovel_winownovel == 0) {

									ClearDrawScreen();
									GAMEMENU_COUNT = 1;

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {

										// ���ʂ̐ݒ�
										ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 0;
									DrawPointX = 0;

									if (SP != 0) {
										SP = SP - 1;
										CP = EOF;
									}

									if (SP == 0) {
										SP = 0;
										CP = 0;
									}

									MessageBox(
										NULL,
										"���[�h���܂����I",
										"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
										MB_OK
									);

									WaitTimer(300);
								}

								//�E�C���h�E���`�掞�̏���
								if (soundnovel_winownovel == 1) {

									ClearDrawScreen();
									GAMEMENU_COUNT = 1;

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									int	Window_Color = GetColor(0, 0, 0);

									DrawBox(0, 400, 640, 480, Window_Color, TRUE);

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {

										// ���ʂ̐ݒ�
										ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 400;
									DrawPointX = 0;

									if (SP != 0) {
										SP = SP - 1;
										CP = EOF;
									}

									if (SP == 0) {
										SP = 0;
										CP = 0;
									}

									MessageBox(
										NULL,
										"���[�h���܂����I",
										"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
										MB_OK
									);

									WaitTimer(300);
								}

								MessageBox(
									NULL,
									"���[�h���܂����I",
									"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
									MB_OK
								);

								break;
							}

							WaitTimer(300);
						}

						//���j���[�ɖ߂�
						if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
							SAVE = MessageBox(
								NULL,
								"���j���[�ɖ߂�܂����H",
								"�m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								ClearDrawScreen();
								SaveFlag = 0;
								WaitTimer(300);

								break;
							}

							WaitTimer(300);
						}
					}
				}

				WaitTimer(300);

			}

			//�Z�[�u�f�[�^�폜
			if (GAME_y == (GAMEMENU_y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 3) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�Z�[�u�f�[�^�폜��ʂɈڍs���܂����H",
					"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					ClearDrawScreen();
					SaveFlag = 3;
					SAVE_y = SAVE_Y;
				}

				WaitTimer(300);

				//�Z�[�u�f�[�^�E�폜���
				if (SaveFlag == 3) {

					//�Z�[�u���̃X�N���[���V���b�g�Ǎ�
					SAVESNAP1 = LoadGraph("DATA/SAVE/SAVESNAP1.png");
					SAVESNAP2 = LoadGraph("DATA/SAVE/SAVESNAP2.png");
					SAVESNAP3 = LoadGraph("DATA/SAVE/SAVESNAP3.png");
					SAVETITLE = LoadGraph("DATA/BACKGROUND/SAVE.png");

					WaitTimer(600);

					while (ProcessMessage() == 0 && MoveKey(Key) == 0) {

						//�w�i�`��
						DrawGraph(0, 0, SAVETITLE, TRUE);

						SAVE_LOAD_MENU(Cr, SAVE_y);

						//�X�N���[���V���b�g�`��
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y, 0.2f, 0, SAVESNAP1, TRUE);
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 2, 0.2f, 0, SAVESNAP2, TRUE);
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 3, 0.2f, 0, SAVESNAP3, TRUE);

						//�Z�[�u�f�[�^���`��
						DrawString(SAVE_NAME_X, SAVE_Y, "�Z�[�u�f�[�^1", Cr);
						DrawString(SAVE_NAME_X, SAVE_Y * 2, "�Z�[�u�f�[�^2", Cr);
						DrawString(SAVE_NAME_X, SAVE_Y * 3, "�Z�[�u�f�[�^3", Cr);
						DrawString(SAVE_NAME_X - CURSOR, SAVE_Y * 4, "���j���[�ɖ߂�", Cr);

						//�L�[����֘A
						SetDrawScreen(DX_SCREEN_BACK);

						ClearDrawScreen();

						//�}�E�X����
						Mouse_Move();

						if (Key[KEY_INPUT_DOWN] == 1) {
							ClearDrawScreen();
							SAVE_y += SAVE_MOVE;
							if (SAVE_y == (SAVE_Y_MAX + SAVE_MOVE + SAVE_MOVE))
								SAVE_y = SAVE_MOVE;
						}

						if (Key[KEY_INPUT_UP] == 1) {
							ClearDrawScreen();
							SAVE_y -= SAVE_MOVE;
							if (SAVE_y == (SAVE_Y - SAVE_MOVE))
								SAVE_y = SAVE_Y_MAX + SAVE_MOVE;
						}

						SetDrawScreen(DX_SCREEN_FRONT);

						if (SAVE_y == SAVE_Y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == SAVE_Y && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"�Z�[�u�f�[�^1���폜���܂����H",
								"�m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								SAVE_DATA_DELETE = "DATA/SAVE/SAVEDATA1.dat";
								remove(SAVE_DATA_DELETE);

								SAVE_DATA_DELETE = "DATA/SAVE/SAVESNAP1.png";
								remove(SAVE_DATA_DELETE);

								MessageBox(
									NULL,
									"�폜���܂����I",
									"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
									MB_OK
									);

								if (soundnovel_winownovel == 0) {

									GAMEMENU_COUNT = 1;
									SaveFlag = 0;
									ClearDrawScreen();

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {
										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 0;
									DrawPointX = 0;
									SP = SP - 1;
									CP = EOF;

									WaitTimer(300);

									break;
								}


								if (soundnovel_winownovel == 1) {

									GAMEMENU_COUNT = 1;
									SaveFlag = 0;
									ClearDrawScreen();

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									int	Window_Color = GetColor(0, 0, 0);

									DrawBox(0, 400, 640, 480, Window_Color, TRUE);

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {
										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 400;
									DrawPointX = 0;
									SP = SP - 1;
									CP = EOF;

									WaitTimer(300);

									break;
								}


							}

							WaitTimer(300);
						}

						if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"�Z�[�u�f�[�^2���폜���܂����H",
								"�m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								SAVE_DATA_DELETE = "DATA/SAVE/SAVEDATA2.dat";
								remove(SAVE_DATA_DELETE);

								SAVE_DATA_DELETE = "DATA/SAVE/SAVESNAP2.png";
								remove(SAVE_DATA_DELETE);

								MessageBox(
									NULL,
									"�폜���܂����I",
									"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
									MB_OK
									);

								if (soundnovel_winownovel == 0) {

									GAMEMENU_COUNT = 1;
									SaveFlag = 0;
									ClearDrawScreen();

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {
										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 0;
									DrawPointX = 0;
									SP = SP - 1;
									CP = EOF;

									WaitTimer(300);

									break;
								}

								if (soundnovel_winownovel == 1) {

									GAMEMENU_COUNT = 1;
									SaveFlag = 0;
									ClearDrawScreen();

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									int	Window_Color = GetColor(0, 0, 0);

									DrawBox(0, 400, 640, 480, Window_Color, TRUE);

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {
										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 400;
									DrawPointX = 0;
									SP = SP - 1;
									CP = EOF;

									WaitTimer(300);

									break;
								}

							}

							WaitTimer(300);
						}

						if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"�Z�[�u�f�[�^3���폜���܂����H",
								"�m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								SAVE_DATA_DELETE = "DATA/SAVE/SAVEDATA3.dat";
								remove(SAVE_DATA_DELETE);

								SAVE_DATA_DELETE = "DATA/SAVE/SAVESNAP3.png";
								remove(SAVE_DATA_DELETE);

								MessageBox(
									NULL,
									"�폜���܂����I",
									"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
									MB_OK
									);

								if (soundnovel_winownovel == 0) {

									GAMEMENU_COUNT = 1;
									SaveFlag = 0;
									ClearDrawScreen();

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {
										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 0;
									DrawPointX = 0;
									SP = SP - 1;
									CP = EOF;

									WaitTimer(300);

									break;
								}

								if (soundnovel_winownovel == 1) {

									GAMEMENU_COUNT = 1;
									SaveFlag = 0;
									ClearDrawScreen();

									//�w�i�̕\��
									if (BACKGROUND != 0) {
										DrawGraph(0, 0, BACKGROUND, TRUE);
									}

									int	Window_Color = GetColor(0, 0, 0);

									DrawBox(0, 400, 640, 480, Window_Color, TRUE);

									//�����G�̕\��
									if (CHARACTER != 0) {
										DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
									}

									//�a�f�l�̍Đ�
									if (BACKGROUNDMUSIC != 0) {
										PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
									}

									DrawPointY = 400;
									DrawPointX = 0;
									SP = SP - 1;
									CP = EOF;

									WaitTimer(300);

									break;
								}
							}

							WaitTimer(300);
						}

						if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"���j���[�ɖ߂�܂����H",
								"�m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								SaveFlag = 0;
								ClearDrawScreen();

								WaitTimer(300);

								break;
							}

							WaitTimer(300);
						}
					}
				}

			}

			//���ǃX�L�b�v
			if (GAME_y == (GAMEMENU_y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 4) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SKIP_READ_LOAD();

				SAVE = MessageBox(
					NULL,
					"���ǃX�L�b�v�����s���܂����H",
					"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (EndFlag == 1 && SAVE == IDYES && LINKS == 1)
					skip_auto = 2;

				if (EndFlag == 2 && SAVE == IDYES && A == 1)
					skip_auto = 2;

				if (EndFlag == 3 && SAVE == IDYES && B == 1)
					skip_auto = 2;

				if (EndFlag == 4 && SAVE == IDYES && C == 1)
					skip_auto = 2;

				if (EndFlag == 5 && SAVE == IDYES && D == 1)
					skip_auto = 2;

				if (EndFlag == 6 && SAVE == IDYES && E == 1)
					skip_auto = 2;

				if (EndFlag == 7 && SAVE == IDYES && F == 1)
					skip_auto = 2;

				if (EndFlag == 8 && SAVE == IDYES && G == 1)
					skip_auto = 2;

				if (EndFlag == 9 && SAVE == IDYES && H == 1)
					skip_auto = 2;

				if (EndFlag == 10 && SAVE == IDYES && I == 1)
					skip_auto = 2;

				if (EndFlag == 11 && SAVE == IDYES && J == 1)
					skip_auto = 2;

				if (EndFlag == 12 && SAVE == IDYES && K == 1)
					skip_auto = 2;

				if (EndFlag == 13 && SAVE == IDYES && L == 1)
					skip_auto = 2;

				if (EndFlag == 14 && SAVE == IDYES && M == 1)
					skip_auto = 2;

				if (EndFlag == 15 && SAVE == IDYES && N == 1)
					skip_auto = 2;

				if (SAVE == IDYES) {

					if (soundnovel_winownovel == 0) {
						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 0;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						WaitTimer(300);

						break;
					}

					if (soundnovel_winownovel == 1) {
						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						int	Window_Color = GetColor(0, 0, 0);

						DrawBox(0, 400, 640, 480, Window_Color, TRUE);

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 400;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						WaitTimer(300);

						break;
					}
				}

				WaitTimer(300);
			}

			//�X�L�b�v
			if (GAME_y == (GAMEMENU_y * 5) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 5) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�X�L�b�v�����s���܂����H",
					"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);
				if (SAVE == IDYES) {

					if (soundnovel_winownovel == 0) {
						ClearDrawScreen();
						skip_auto = 2;
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 0;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						WaitTimer(300);

						break;
					}

					if (soundnovel_winownovel == 1) {
						ClearDrawScreen();
						skip_auto = 2;
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						int	Window_Color = GetColor(0, 0, 0);

						DrawBox(0, 400, 640, 480, Window_Color, TRUE);

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 400;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						WaitTimer(300);

						break;
					}
				}

				WaitTimer(300);
			}

			//�I�[�g
			if (GAME_y == (GAMEMENU_y * 6) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 6) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�I�[�g���[�h�����s���܂����H",
					"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);
				if (SAVE == IDYES) {

					if (soundnovel_winownovel == 0) {
						ClearDrawScreen();
						skip_auto = 1;
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 0;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						WaitTimer(300);

						break;
					}

					if (soundnovel_winownovel == 1) {
						ClearDrawScreen();
						skip_auto = 1;
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						int	Window_Color = GetColor(0, 0, 0);

						DrawBox(0, 400, 640, 480, Window_Color, TRUE);

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 400;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						WaitTimer(300);

						break;
					}


				}

				WaitTimer(300);
			}

			//�I�[�g/�X�L�b�v��~
			if (GAME_y == (GAMEMENU_y * 7) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 7) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�X�L�b�v���̓I�[�g���[�h���I�����܂����H",
					"�m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					if (soundnovel_winownovel == 0) {
						ClearDrawScreen();
						skip_auto = 0;
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 0;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						WaitTimer(300);

						break;
					}

					if (soundnovel_winownovel == 1) {
						ClearDrawScreen();
						skip_auto = 0;
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						int	Window_Color = GetColor(0, 0, 0);

						DrawBox(0, 400, 640, 480, Window_Color, TRUE);

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 400;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						WaitTimer(300);

						break;
					}
				}

				WaitTimer(300);
			}

			//�o�b�N���O�Q��
			if (GAME_y == (GAMEMENU_y * 8) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 8) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�o�b�N���O��ʂɈڍs���܂����H",
					"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					WaitTimer(600);

					LOG = 1;

					while (ProcessMessage() == 0) {

						if (LOG != 10 && CheckHitKey(KEY_INPUT_UP) == 1 || LOG != 10 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
							LOG++;
							WaitTimer(300);
						}

						if (LOG != 1 && CheckHitKey(KEY_INPUT_DOWN) == 1 || LOG != 1 && (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
							LOG--;
							WaitTimer(300);
						}

						if (LOG == 1) {
							DrawGraph(0, 0, BACKLOG[0], TRUE);
							DrawString(0, 450, "�o�b�N���O1", Cr);
						}
						if (LOG == 2) {
							DrawGraph(0, 0, BACKLOG[1], TRUE);
							DrawString(0, 450, "�o�b�N���O2", Cr);
						}
						if (LOG == 3) {
							DrawGraph(0, 0, BACKLOG[2], TRUE);
							DrawString(0, 450, "�o�b�N���O3", Cr);
						}
						if (LOG == 4) {
							DrawGraph(0, 0, BACKLOG[3], TRUE);
							DrawString(0, 450, "�o�b�N���O4", Cr);
						}
						if (LOG == 5) {
							DrawGraph(0, 0, BACKLOG[4], TRUE);
							DrawString(0, 450, "�o�b�N���O5", Cr);
						}
						if (LOG == 6) {
							DrawGraph(0, 0, BACKLOG[5], TRUE);
							DrawString(0, 450, "�o�b�N���O6", Cr);
						}
						if (LOG == 7) {
							DrawGraph(0, 0, BACKLOG[6], TRUE);
							DrawString(0, 450, "�o�b�N���O7", Cr);
						}
						if (LOG == 8) {
							DrawGraph(0, 0, BACKLOG[7], TRUE);
							DrawString(0, 450, "�o�b�N���O8", Cr);
						}
						if (LOG == 9) {
							DrawGraph(0, 0, BACKLOG[8], TRUE);
							DrawString(0, 450, "�o�b�N���O9", Cr);
						}
						if (LOG == 10) {
							DrawGraph(0, 0, BACKLOG[9], TRUE);
							DrawString(0, 450, "�o�b�N���O10", Cr);
						}

						SetDrawScreen(DX_SCREEN_BACK);

						ClearDrawScreen();

						SetDrawScreen(DX_SCREEN_FRONT);

						if (CheckHitKey(KEY_INPUT_RETURN) == 1 || (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							ClearDrawScreen();

							DeleteGraph(BACKLOG[0]);

							WaitTimer(300);

							break;
						}
					}
				}

				WaitTimer(300);
			}

			//�ݒ�
			if (GAME_y == (GAMEMENU_y * 9) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 9) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�ݒ��ύX���܂����H",
					"�m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					Config = 1;

					GAME_y = GAMEMENU_y;

					ClearDrawScreen();

					WaitTimer(300);

					while (ProcessMessage() == 0 && MoveKey(Key) == 0 && Config == 1) {

						GAME_MENU_CURSOR(Cr, GAME_y);

						//�Z�[�u�f�[�^���`��
						DrawString(SAVE_NAME_X, GAMEMENU_y, "�a�f�l����", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 2, "�r�d����", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 3, "�I�[�g���x", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 4, "�X�L�b�v���x", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 5, "�����`�摬�x", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 6, "�`����@", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 7, "��A�N�e�B�u��", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 8, "���j���[�ɖ߂�", Cr);

						//�ڐ���`��

						if (BGM_VOL_COUNT == 10)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "��������������������", Cr);

						if (BGM_VOL_COUNT == 9)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "������������������", Cr);

						if (BGM_VOL_COUNT == 8)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "����������������", Cr);

						if (BGM_VOL_COUNT == 7)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "��������������", Cr);

						if (BGM_VOL_COUNT == 6)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "������������", Cr);

						if (BGM_VOL_COUNT == 5)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "����������", Cr);

						if (BGM_VOL_COUNT == 4)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "��������", Cr);

						if (BGM_VOL_COUNT == 3)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "������", Cr);

						if (BGM_VOL_COUNT == 2)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "����", Cr);

						if (BGM_VOL_COUNT == 1)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "��", Cr);

						if (BGM_VOL_COUNT == 0)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "", Cr);

						if (SE_VOL_COUNT == 10)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "��������������������", Cr);

						if (SE_VOL_COUNT == 9)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "������������������", Cr);

						if (SE_VOL_COUNT == 8)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "����������������", Cr);

						if (SE_VOL_COUNT == 7)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "��������������", Cr);

						if (SE_VOL_COUNT == 6)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "������������", Cr);

						if (SE_VOL_COUNT == 5)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "����������", Cr);

						if (SE_VOL_COUNT == 4)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "��������", Cr);

						if (SE_VOL_COUNT == 3)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "������", Cr);

						if (SE_VOL_COUNT == 2)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "����", Cr);

						if (SE_VOL_COUNT == 1)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "��", Cr);

						if (SE_VOL_COUNT == 0)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "", Cr);

						if (AUTO_SPEED_COUNT == 10)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "��������������������", Cr);

						if (AUTO_SPEED_COUNT == 9)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "������������������", Cr);

						if (AUTO_SPEED_COUNT == 8)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "����������������", Cr);

						if (AUTO_SPEED_COUNT == 7)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "��������������", Cr);

						if (AUTO_SPEED_COUNT == 6)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "������������", Cr);

						if (AUTO_SPEED_COUNT == 5)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "����������", Cr);

						if (AUTO_SPEED_COUNT == 4)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "��������", Cr);

						if (AUTO_SPEED_COUNT == 3)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "������", Cr);

						if (AUTO_SPEED_COUNT == 2)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "����", Cr);

						if (AUTO_SPEED_COUNT == 1)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "��", Cr);

						if (AUTO_SPEED_COUNT == 0)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "", Cr);

						if (SKIP_SPEED_COUNT == 10)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "��������������������", Cr);

						if (SKIP_SPEED_COUNT == 9)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "������������������", Cr);

						if (SKIP_SPEED_COUNT == 8)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "����������������", Cr);

						if (SKIP_SPEED_COUNT == 7)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "��������������", Cr);

						if (SKIP_SPEED_COUNT == 6)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "������������", Cr);

						if (SKIP_SPEED_COUNT == 5)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "����������", Cr);

						if (SKIP_SPEED_COUNT == 4)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "��������", Cr);

						if (SKIP_SPEED_COUNT == 3)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "������", Cr);

						if (SKIP_SPEED_COUNT == 2)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "����", Cr);

						if (SKIP_SPEED_COUNT == 1)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "��", Cr);

						if (SKIP_SPEED_COUNT == 0)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "", Cr);


						if (STRING_SPEED_COUNT == 10)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "��������������������", Cr);

						if (STRING_SPEED_COUNT == 9)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "������������������", Cr);

						if (STRING_SPEED_COUNT == 8)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "����������������", Cr);

						if (STRING_SPEED_COUNT == 7)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "��������������", Cr);

						if (STRING_SPEED_COUNT == 6)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "������������", Cr);

						if (STRING_SPEED_COUNT == 5)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "����������", Cr);

						if (STRING_SPEED_COUNT == 4)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "��������", Cr);

						if (STRING_SPEED_COUNT == 3)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "������", Cr);

						if (STRING_SPEED_COUNT == 2)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "����", Cr);

						if (STRING_SPEED_COUNT == 1)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "��", Cr);

						if (STRING_SPEED_COUNT == 0)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "", Cr);

						if (soundnovel_winownovel == 0)
							DrawString(SAVE_NAME_X + CURSOR * 6, GAMEMENU_y * 6, "�T�E���h�m�x����", Cr);

						if (soundnovel_winownovel == 1)
							DrawString(SAVE_NAME_X + CURSOR * 6, GAMEMENU_y * 6, "�E�C���h�E��", Cr);

						if (WindowActive == TRUE)
							DrawString(SAVE_NAME_X + CURSOR * 7, GAMEMENU_y * 7, "����", Cr);

						if (WindowActive == FALSE)
							DrawString(SAVE_NAME_X + CURSOR * 7, GAMEMENU_y * 7, "������", Cr);

						//�a�f�l���ʒ���
						if (GAME_y == GAMEMENU_y && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

							WaitTimer(300);

							BGM_VOL += 10;
							BGM_VOL_COUNT += 1;

							if (BGM_VOL_COUNT >= 10) {
								BGM_VOL = 100;
								BGM_VOL_COUNT = 10;
							}
						}

						if (GAME_y == GAMEMENU_y && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

							WaitTimer(300);

							BGM_VOL -= 10;
							BGM_VOL_COUNT -= 1;

							if (BGM_VOL_COUNT <= 0) {
								BGM_VOL = 0;
								BGM_VOL_COUNT = 0;
							}
						}

						//�r�d���ʒ���
						if (GAME_y == GAMEMENU_y * 2 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 2 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

							WaitTimer(300);

							SE_VOL += 10;
							SE_VOL_COUNT += 1;

							if (SE_VOL_COUNT >= 10) {
								SE_VOL = 100;
								SE_VOL_COUNT = 10;
							}
						}

						if (GAME_y == GAMEMENU_y * 2 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 2 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

							WaitTimer(300);

							SE_VOL -= 10;
							SE_VOL_COUNT -= 1;

							if (SE_VOL_COUNT <= 0) {
								SE_VOL = 0;
								SE_VOL_COUNT = 0;
							}
						}

						//�I�[�g���x����
						if (GAME_y == GAMEMENU_y * 3 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 3 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

							WaitTimer(300);

							AUTO_SPEED += 10;
							AUTO_SPEED_COUNT += 1;

							if (AUTO_SPEED_COUNT >= 10) {
								AUTO_SPEED = 100;
								AUTO_SPEED_COUNT = 10;
							}
						}

						if (GAME_y == GAMEMENU_y * 3 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 3 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

							WaitTimer(300);

							AUTO_SPEED -= 10;
							AUTO_SPEED_COUNT -= 1;

							if (AUTO_SPEED_COUNT <= 0) {
								AUTO_SPEED = 0;
								AUTO_SPEED_COUNT = 0;
							}
						}

						//�X�L�b�v���x����
						if (GAME_y == GAMEMENU_y * 4 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 4 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

							WaitTimer(300);

							SKIP_SPEED += 10;
							SKIP_SPEED_COUNT += 1;

							if (SKIP_SPEED_COUNT >= 10) {
								SKIP_SPEED = 100;
								SKIP_SPEED_COUNT = 10;
							}
						}

						if (GAME_y == GAMEMENU_y * 4 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 4 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

							WaitTimer(300);

							SKIP_SPEED -= 10;
							SKIP_SPEED_COUNT -= 1;

							if (SKIP_SPEED_COUNT <= 0) {
								SKIP_SPEED = 0;
								SKIP_SPEED_COUNT = 0;
							}

						}

						//�����`�摬�x����
						if (GAME_y == GAMEMENU_y * 5 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 5 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

							WaitTimer(300);

							STRING_SPEED += 10;
							STRING_SPEED_COUNT += 1;

							if (STRING_SPEED_COUNT >= 10) {
								STRING_SPEED = 100;
								STRING_SPEED_COUNT = 10;
							}
						}

						if (GAME_y == GAMEMENU_y * 5 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 5 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

							WaitTimer(300);

							STRING_SPEED -= 10;
							STRING_SPEED_COUNT -= 1;

							if (STRING_SPEED_COUNT <= 0) {
								STRING_SPEED = 0;
								STRING_SPEED_COUNT = 0;
							}

						}

						//�T�E���h�m�x�����ƃE�C���h�E���̐؂�ւ�
						if (GAME_y == GAMEMENU_y * 6 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 6 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

							WaitTimer(300);
							soundnovel_winownovel = 0;
						}

						if (GAME_y == GAMEMENU_y * 6 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 6 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

							WaitTimer(300);
							soundnovel_winownovel = 1;
						}

						//��A�N�e�B�u���̏����̐؂�ւ�
						if (GAME_y == GAMEMENU_y * 7 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 7 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

							WaitTimer(300);
							WindowActive = FALSE;

							//��A�N�e�B�u��Ԃł͏��������s���Ȃ�
							SetAlwaysRunFlag(WindowActive);
						}

						if (GAME_y == GAMEMENU_y * 7 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 7 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

							WaitTimer(300);
							WindowActive = TRUE;

							//��A�N�e�B�u��Ԃł��Q�[�������s
							SetAlwaysRunFlag(WindowActive);
						}

						//���j���[�ɖ߂�
						if (GAME_y == GAMEMENU_y * 8 && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == GAMEMENU_y * 8 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

							SAVE = MessageBox(
								NULL,
								"���j���[�ɖ߂�܂����H",
								"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
								MB_YESNO
								);

							if (SAVE == IDYES) {
								WaitTimer(300);
								ClearDrawScreen();
								GAME_y = GAMEMENU_y;
								Config = 0;
								break;
							}

							WaitTimer(300);
						}

						//�L�[����֘A
						SetDrawScreen(DX_SCREEN_BACK);

						ClearDrawScreen();

						Mouse_Move();

						if (Key[KEY_INPUT_DOWN] == 1) {
							ClearDrawScreen();
							GAME_y += GAMEMENU_y;
							if (GAME_y == (GAMEMENU_y * 9))
								GAME_y = GAMEMENU_y;
						}

						if (Key[KEY_INPUT_UP] == 1) {
							ClearDrawScreen();
							GAME_y -= GAMEMENU_y;
							if (GAME_y == (GAMEMENU_y - GAMEMENU_y))
								GAME_y = (GAMEMENU_y * 8);
						}

						SetDrawScreen(DX_SCREEN_FRONT);


					}
				}

				WaitTimer(300);

			}

			//�^�C�g���ɖ߂�
			if (GAME_y == (GAMEMENU_y * 10) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 10) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�^�C�g����ʂɖ߂�܂����H",
					"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {
					ClearDrawScreen();
					GAMEMENU_COUNT = 1;
					EndFlag = 99;
					y = MENUY;
					skip_auto = 0;
					SaveFlag = 0;
					CHARACTER = 0;
					BACKGROUND = 0;
					BACKGROUNDMUSIC = 0;

					WaitTimer(300);

					break;
				}

				WaitTimer(300);

			}

			//�Q�[���ɖ߂�
			if (GAME_y == (GAMEMENU_y * 11) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 11) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�Q�[���ɖ߂�܂����H",
					"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					if (soundnovel_winownovel == 0) {
						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 0;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						WaitTimer(300);

						break;
					}

					if (soundnovel_winownovel == 1) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

						//�w�i�̕\��
						if (BACKGROUND != 0) {
							DrawGraph(0, 0, BACKGROUND, TRUE);
						}

						int	Window_Color = GetColor(0, 0, 0);

						DrawBox(0, 400, 640, 480, Window_Color, TRUE);

						//�����G�̕\��
						if (CHARACTER != 0) {
							DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
						}

						//�a�f�l�̍Đ�
						if (BACKGROUNDMUSIC != 0) {

							// ���ʂ̐ݒ�
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

							PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
						}

						DrawPointY = 400;
						DrawPointX = 0;

						if (SP != 0) {
							SP = SP - 1;
							CP = EOF;
						}

						if (SP == 0) {
							SP = 0;
							CP = 0;
						}

						WaitTimer(300);

						break;
					}

				}

				WaitTimer(300);
			}

			//�Q�[���I��
			if (GAME_y == (GAMEMENU_y * 12) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 12) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�I�����܂����H",
					"�m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);
				
				if (SAVE == IDYES) {

					//�N�C�b�N�Z�[�u
					QUICKSAVE_SAVE();

					EndFlag = 99999;
					break;
				}

				WaitTimer(300);
			}

			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {

				SAVE = MessageBox(
					NULL,
					"�I�����܂����H",
					"�m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					EndFlag = 99999;
					break;
				}

				WaitTimer(300);
			}
		}
	}

	return 0;

}

//�I�����@�\
void sentakusi(int Cr, int y) {

	//�J�[�\���̕`��
	DrawString(SENTAKUSIX, y, "��", Cr);
	
	//�I�����̕`��
	DrawString(SENTAKUSIX + CURSOR, SENTAKUSI1, ChoiceA, Cr);
	DrawString(SENTAKUSIX + CURSOR, SENTAKUSI2, ChoiceB, Cr);
}

// ���s�֐�
int Kaigyou(void)
{
	if (soundnovel_winownovel == 0) {

		int TempGraph;

		// �`��s�ʒu���������
		DrawPointY++;

		// �`�����ŏ��ɖ߂�
		DrawPointX = 0;

		// ������ʂ���͂ݏo��Ȃ��ʂ��X�N���[��������
		if (DrawPointY * MOJI_SIZE + MOJI_SIZE > 480)
		{
			// �e���|�����O���t�B�b�N�̍쐬
			TempGraph = MakeGraph(640, 480);

			// ��ʂ̓��e���ہX�R�s�[����
			GetDrawScreenGraph(0, 0, 640, 480, TempGraph);

			// ��s����ɓ\��t����
			DrawGraph(0, -MOJI_SIZE, TempGraph, FALSE);

			// ��ԉ��̍s�̕��������Ŗ��߂�
			DrawBox(0, 480 - MOJI_SIZE, 640, 480, 0, TRUE);

			// �`��s�ʒu���������
			DrawPointY--;

			// �O���t�B�b�N���폜����
			DeleteGraph(TempGraph);
		}
	}

	if (soundnovel_winownovel == 1) {

		// �`��s�ʒu���������
		DrawPointY += 20;

		// �`�����ŏ��ɖ߂�
		DrawPointX = 0;
	}


	// �I��
	return 0;
}

//�I���E�C���h�E
int GAME_FINISH() {

	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {

		SAVE = MessageBox(
			NULL,
			"�I�����܂����H",
			"�m�x���Q�[���G���W���uLINKS�v",
			MB_YESNO
		);

		if (SAVE == IDYES) {

			QUICKSAVE_SAVE();
			EndFlag = 99999;
		}
	}

	return 0;
}

//�X�N���v�g�^�O�����֐�
int SCRIPT_OUTPUT() {

	char  Moji;

	// �����̕`��
	Moji = String[SP][CP];

	switch (Moji)
	{

		//********************���o����(��������)****************************************//

		// ���s����
	case '0':

		// ���s��������юQ�ƕ����ʒu����i�߂�
		Kaigyou();
		CP++;

		break;

		// �{�^�������҂�����
	case '1':

		//�X�L�b�v�E�I�[�g�ϐ����n�e�e�̏ꍇ
		if (skip_auto == 0) {

			//�Z�[�u�f�[�^�p�X�N���[���V���b�g�ۑ�
			if (SAVESNAP_HANDLE1 == 1) {
				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP1.png", 0);
				SAVESNAP_HANDLE1 = 0;
			}

			if (SAVESNAP_HANDLE2 == 1) {
				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP2.png", 0);
				SAVESNAP_HANDLE2 = 0;
			}

			if (SAVESNAP_HANDLE3 == 1) {
				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP3.png", 0);
				SAVESNAP_HANDLE3 = 0;
			}

			// �{�^�������҂�����юQ�ƕ����ʒu����i�߂�
			WaitKey();

			//�G���^�[�L�[�Ŏ���
			if (CheckHitKey(KEY_INPUT_RETURN) == 1 || (GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
				CP++;
		}

		//�X�L�b�v�E�I�[�g�ϐ����n�m�̏ꍇ�i�I�[�g���[�h�j
		if (skip_auto == 1) {

			//�Z�[�u�f�[�^�p�X�N���[���V���b�g�ۑ�
			if (SAVESNAP_HANDLE1 == 1) {
				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP1.png", 0);
				SAVESNAP_HANDLE1 = 0;
			}

			if (SAVESNAP_HANDLE2 == 1) {
				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP2.png", 0);
				SAVESNAP_HANDLE2 = 0;
			}

			if (SAVESNAP_HANDLE3 == 1) {
				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP3.png", 0);
				SAVESNAP_HANDLE3 = 0;
			}

			//�����҂��āA���̕������`��
			WaitTimer(1800 * AUTO_SPEED / 100);
			CP++;
		}

		//�X�L�b�v�E�I�[�g�ϐ����n�m�̏ꍇ(�X�L�b�v)
		if (skip_auto == 2) {

			//�Z�[�u�f�[�^�p�X�N���[���V���b�g�ۑ�
			if (SAVESNAP_HANDLE1 == 1) {
				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP1.png", 0);
				SAVESNAP_HANDLE1 = 0;
			}

			if (SAVESNAP_HANDLE2 == 1) {
				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP2.png", 0);
				SAVESNAP_HANDLE2 = 0;
			}

			if (SAVESNAP_HANDLE3 == 1) {
				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP3.png", 0);
				SAVESNAP_HANDLE3 = 0;
			}

			CP++;
		}

		break;

		// �N���A����
	case '2':


		SetDrawScreen(DX_SCREEN_BACK);

		BACKLOG_COUNT++;

		if (BACKLOG_COUNT == 1) {

			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;
		}

		if (BACKLOG_COUNT == 2) {

			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

		if (BACKLOG_COUNT == 3) {
		
			BACKLOG_BACKGROUND = BACKLOG[1];

			BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

		if (BACKLOG_COUNT == 4) {

			BACKLOG_BACKGROUND = BACKLOG[2];

			BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[1];

			BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

		if (BACKLOG_COUNT == 5) {

			BACKLOG_BACKGROUND = BACKLOG[3];

			BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[2];

			BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[1];

			BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

		if (BACKLOG_COUNT == 6) {

			BACKLOG_BACKGROUND = BACKLOG[4];

			BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[3];

			BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[2];

			BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[1];

			BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

		if (BACKLOG_COUNT == 7) {

			BACKLOG_BACKGROUND = BACKLOG[5];

			BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[4];

			BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[3];

			BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[2];

			BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[1];

			BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

		if (BACKLOG_COUNT == 8) {

			BACKLOG_BACKGROUND = BACKLOG[6];

			BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[5];

			BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[4];

			BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[3];

			BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[2];

			BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[1];

			BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

		if (BACKLOG_COUNT == 9) {

			BACKLOG_BACKGROUND = BACKLOG[7];

			BACKLOG[8] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[6];

			BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[5];

			BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[4];

			BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[3];

			BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[2];

			BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[1];

			BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

		if (BACKLOG_COUNT >= 10) {

			BACKLOG_BACKGROUND = BACKLOG[8];

			BACKLOG[9] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[7];

			BACKLOG[8] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[6];

			BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[5];

			BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[4];

			BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[3];

			BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[2];

			BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[1];

			BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

		SetDrawScreen(DX_SCREEN_FRONT);
			
		break;

		//�����҂�
	case '3':

		//�I�[�g���͒ʏ펞�A3�b�҂�
		if (skip_auto != 2) {
			WaitTimer(1800);
			CP++;
		}

		//�X�L�b�v���A3�b�҂����Ɏ���
		if (skip_auto == 2)
			CP++;
		
		break;

		//�Q�[���I�[�o�[
	case '4':

		BACKGROUND = GAMEOVER;
		DrawGraph(0, 0, BACKGROUND, TRUE);

		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}

		CP++;
		break;

		//�G���f�B���O
	case '5':

		PlayMovie("DATA/MOVIE/ENDING.wmv", 1, DX_MOVIEPLAYTYPE_NORMAL);
		CP++;

		break;

		//BGM�̍Đ����~�߂�
	case '6':

		StopSoundMem(BACKGROUNDMUSIC);
		BACKGROUNDMUSIC = 0;
		CP++;

		break;

		//SE�̍Đ����~�߂�
	case '7':

		StopSoundMem(SOUNDEFFECT);
		CP++;

		break;

		//
	case '8':
		y = SENTAKUSIY;

		if (EndFlag == 1 || EndFlag == 2 || EndFlag == 3 || EndFlag == 4 || EndFlag == 5 || EndFlag == 6 || EndFlag == 7) {

			WaitTimer(1200);

			SAVE_CHOICE = 1;
			SAVESNAP_CHOICE = 1;

			BACKLOG_COUNT++;

			//�I����

			while (ProcessMessage() == 0 && MoveKey(Key) == 0 && EndFlag != 99 && EndFlag != 99999) {

				if (soundnovel_winownovel == 0) {

					DrawGraph(0, 0, BACKGROUND, TRUE);

					DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
				}

				if (soundnovel_winownovel == 1) {

					int	Window_Color = GetColor(0, 0, 0);

					DrawGraph(0, 0, BACKGROUND, TRUE);
					
					DrawBox(0, 400, 640, 480, Window_Color, TRUE);

					DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
				}

				if (EndFlag == 1) {
					//�I����A���J��
					Choice1 = FileRead_open("DATA/STR/CHOICE/A.txt");
					FileRead_gets(ChoiceA, RETU, Choice1);

					//�I����B���J��
					Choice2 = FileRead_open("DATA/STR/CHOICE/B.txt");
					FileRead_gets(ChoiceB, RETU, Choice2);
				}

				if (EndFlag == 2) {
					//�I����C���J��
					Choice1 = FileRead_open("DATA/STR/CHOICE/C.txt");
					FileRead_gets(ChoiceA, RETU, Choice1);

					//�I����D���J��
					Choice2 = FileRead_open("DATA/STR/CHOICE/D.txt");
					FileRead_gets(ChoiceB, RETU, Choice2);
				}

				if (EndFlag == 3) {
					//�I����E���J��
					Choice1 = FileRead_open("DATA/STR/CHOICE/E.txt");
					FileRead_gets(ChoiceA, RETU, Choice1);

					//�I����F���J��
					Choice2 = FileRead_open("DATA/STR/CHOICE/F.txt");
					FileRead_gets(ChoiceB, RETU, Choice2);
				}

				if (EndFlag == 4) {
					//�I����G���J��
					Choice1 = FileRead_open("DATA/STR/CHOICE/G.txt");
					FileRead_gets(ChoiceA, RETU, Choice1);

					//�I����H���J��
					Choice2 = FileRead_open("DATA/STR/CHOICE/H.txt");
					FileRead_gets(ChoiceB, RETU, Choice2);
				}

				if (EndFlag == 5) {
					//�I����I���J��
					Choice1 = FileRead_open("DATA/STR/CHOICE/I.txt");
					FileRead_gets(ChoiceA, RETU, Choice1);

					//�I����J���J��
					Choice2 = FileRead_open("DATA/STR/CHOICE/J.txt");
					FileRead_gets(ChoiceB, RETU, Choice2);
				}

				if (EndFlag == 6) {
					//�I����K���J��
					Choice1 = FileRead_open("DATA/STR/CHOICE/K.txt");
					FileRead_gets(ChoiceA, RETU, Choice1);

					//�I����L���J��
					Choice2 = FileRead_open("DATA/STR/CHOICE/L.txt");
					FileRead_gets(ChoiceB, RETU, Choice2);
				}

				if (EndFlag == 7) {
					//�I����M���J��
					Choice1 = FileRead_open("DATA/STR/CHOICE/M.txt");
					FileRead_gets(ChoiceA, RETU, Choice1);

					//�I����N���J��
					Choice2 = FileRead_open("DATA/STR/CHOICE/N.txt");
					FileRead_gets(ChoiceB, RETU, Choice2);
				}

				sentakusi(Cr, y);

				//�Q�[�����j���[
				GAMEMENU();

				//�Q�[���I��
				GAME_FINISH();

				if (SAVESNAP_CHOICE == 1) {

					SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP_CHOICE.png", 0);

					SAVESNAP_CHOICE = LoadGraph("DATA/SAVE/SAVESNAP_CHOICE.png", 0);

				}

				//�L�[����֘A
				SetDrawScreen(DX_SCREEN_BACK);

				ClearDrawScreen();

				Mouse_Move();

				if (Key[KEY_INPUT_DOWN] == 1) {
					ClearDrawScreen();
					y += CURSOR;
					if (y == (SENTAKUSI2 + CURSOR))                         // y���W��260�Ȃ�(�I������ԉ��Ȃ�)
						y = SENTAKUSI1;                        // �I�����W����ԏ��
				}
				if (Key[KEY_INPUT_UP] == 1) {
					ClearDrawScreen();
					y -= CURSOR;
					if (y == (SENTAKUSI1 - CURSOR))
						y = SENTAKUSI2;
				}

				SetDrawScreen(DX_SCREEN_FRONT);

				if (y == SENTAKUSI1 && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == SENTAKUSI1 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

					if (EndFlag == 1) {
						EndFlag = 2;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 2) {
						EndFlag = 4;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 3) {
						EndFlag = 6;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 4) {
						EndFlag = 8;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 5) {
						EndFlag = 10;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 6) {
						EndFlag = 12;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 7) {
						EndFlag = 14;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

				}

				if (y == SENTAKUSI2 && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == SENTAKUSI2 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

					if (EndFlag == 1) {
						EndFlag = 3;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 2) {
						EndFlag = 5;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 3) {
						EndFlag = 7;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 4) {
						EndFlag = 9;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 5) {
						EndFlag = 11;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 6) {
						EndFlag = 13;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 7) {
						EndFlag = 15;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					CP++;
					break;
				}

			}


			SetDrawScreen(DX_SCREEN_BACK);

			if (soundnovel_winownovel == 0) {

				DrawGraph(0, 0, BACKGROUND, TRUE);

				DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			}

			if (soundnovel_winownovel == 1) {

				int	Window_Color = GetColor(0, 0, 0);

				DrawGraph(0, 0, BACKGROUND, TRUE);

				DrawBox(0, 400, 640, 480, Window_Color, TRUE);

				DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			}

			if (EndFlag == 2 || EndFlag == 3) {
				//�I����A���J��
				Choice1 = FileRead_open("DATA/STR/CHOICE/A.txt");
				FileRead_gets(ChoiceA, RETU, Choice1);

				//�I����B���J��
				Choice2 = FileRead_open("DATA/STR/CHOICE/B.txt");
				FileRead_gets(ChoiceB, RETU, Choice2);
			}

			if (EndFlag == 4 || EndFlag == 5) {
				//�I����C���J��
				Choice1 = FileRead_open("DATA/STR/CHOICE/C.txt");
				FileRead_gets(ChoiceA, RETU, Choice1);

				//�I����D���J��
				Choice2 = FileRead_open("DATA/STR/CHOICE/D.txt");
				FileRead_gets(ChoiceB, RETU, Choice2);
			}

			if (EndFlag == 6 || EndFlag == 7) {
				//�I����E���J��
				Choice1 = FileRead_open("DATA/STR/CHOICE/E.txt");
				FileRead_gets(ChoiceA, RETU, Choice1);

				//�I����F���J��
				Choice2 = FileRead_open("DATA/STR/CHOICE/F.txt");
				FileRead_gets(ChoiceB, RETU, Choice2);
			}

			if (EndFlag == 8 || EndFlag == 9) {
				//�I����G���J��
				Choice1 = FileRead_open("DATA/STR/CHOICE/G.txt");
				FileRead_gets(ChoiceA, RETU, Choice1);

				//�I����H���J��
				Choice2 = FileRead_open("DATA/STR/CHOICE/H.txt");
				FileRead_gets(ChoiceB, RETU, Choice2);
			}

			if (EndFlag == 10 || EndFlag == 11) {
				//�I����I���J��
				Choice1 = FileRead_open("DATA/STR/CHOICE/I.txt");
				FileRead_gets(ChoiceA, RETU, Choice1);

				//�I����J���J��
				Choice2 = FileRead_open("DATA/STR/CHOICE/J.txt");
				FileRead_gets(ChoiceB, RETU, Choice2);
			}

			if (EndFlag == 12 || EndFlag == 13) {
				//�I����K���J��
				Choice1 = FileRead_open("DATA/STR/CHOICE/K.txt");
				FileRead_gets(ChoiceA, RETU, Choice1);

				//�I����L���J��
				Choice2 = FileRead_open("DATA/STR/CHOICE/L.txt");
				FileRead_gets(ChoiceB, RETU, Choice2);
			}

			if (EndFlag == 14 || EndFlag == 15) {
				//�I����M���J��
				Choice1 = FileRead_open("DATA/STR/CHOICE/M.txt");
				FileRead_gets(ChoiceA, RETU, Choice1);

				//�I����N���J��
				Choice2 = FileRead_open("DATA/STR/CHOICE/N.txt");
				FileRead_gets(ChoiceB, RETU, Choice2);
			}

			sentakusi(Cr, y);

			if (BACKLOG_COUNT == 1) {

				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

			}

			if (BACKLOG_COUNT == 2) {

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

			}

			if (BACKLOG_COUNT == 3) {

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 4) {

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 5) {

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 6) {

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 7) {

				BACKLOG_BACKGROUND = BACKLOG[5];

				BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 8) {

				BACKLOG_BACKGROUND = BACKLOG[6];

				BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[5];

				BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 9) {

				BACKLOG_BACKGROUND = BACKLOG[7];

				BACKLOG[8] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[6];

				BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[5];

				BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT >= 10) {

				BACKLOG_BACKGROUND = BACKLOG[8];

				BACKLOG[9] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[7];

				BACKLOG[8] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[6];

				BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[5];

				BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			SetDrawScreen(DX_SCREEN_FRONT);

			// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
			SetDrawScreen(DX_SCREEN_BACK);

			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

			SetDrawScreen(DX_SCREEN_FRONT);

			break;
		}

		if (EndFlag == 8 || EndFlag == 9 || EndFlag == 10 || EndFlag == 11 || EndFlag == 12 || EndFlag == 13 || EndFlag == 14 || EndFlag == 15) {
			CP++;
			break;
		}

		// �I������
	case '9':

		if (EndFlag == 1)
			LINKS = 1;

		if (EndFlag == 2)
			A = 1;

		if (EndFlag == 3)
			B = 1;

		if (EndFlag == 4)
			C = 1;

		if (EndFlag == 5)
			D = 1;

		if (EndFlag == 6)
			E = 1;

		if (EndFlag == 7)
			F = 1;

		if (EndFlag == 8)
			G = 1;

		if (EndFlag == 9)
			H = 1;

		if (EndFlag == 10)
			I = 1;

		if (EndFlag == 11)
			J = 1;

		if (EndFlag == 12)
			K = 1;

		if (EndFlag == 13)
			L = 1;

		if (EndFlag == 14)
			M = 1;

		if (EndFlag == 15)
			N = 1;

		SKIP_READ_SAVE();

		// �I���t���O�𗧂Ă邨��юQ�ƕ����ʒu����i�߂�
		EndFlag = 99999;
		CP++;

		break;

		//�����G�����^�O
	case '@':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CP++;
		}

		break;

		//�E�C���h�E���L�����N�^�[���`��^�O
	case '#':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			SP++;
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {

			//�L�����N�^�[����ǂݍ���
			CHARACTER_NAME[0] = String[SP][CP + 1];
			CHARACTER_NAME[1] = String[SP][CP + 2];
			CHARACTER_NAME[2] = String[SP][CP + 3];
			CHARACTER_NAME[3] = String[SP][CP + 4];
			CHARACTER_NAME[4] = String[SP][CP + 5];
			CHARACTER_NAME[5] = String[SP][CP + 6];
			CHARACTER_NAME[6] = String[SP][CP + 7];
			CHARACTER_NAME[7] = String[SP][CP + 8];
			CHARACTER_NAME[8] = String[SP][CP + 9];
			CHARACTER_NAME[9] = '\0';

			//�L�����N�^�[���̔w�i
			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(30, 360, 150, 385, Window_Color, TRUE);

			// �P�����`��
			DrawString(30, 360, CHARACTER_NAME, GetColor(255, 255, 255));

			SP++;
			CP++;
		}

		break;

		//********************���o����(�����܂�)****************************************//

		//********************�L�����N�^�[�摜�Ǎ�����(��������)****************************************//

		//�L����01�Ǎ��i��ʂɏo�́j
	case 'A':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[0];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[0];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		break;

		//�L����02�Ǎ��i��ʂɏo�́j
	case 'B':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[1];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[1];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		break;

		//�L����03�Ǎ��i��ʂɏo�́j
	case 'C':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[2];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[2];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		break;

		//�L����04�Ǎ��i��ʂɏo�́j
	case 'D':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[3];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[3];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		break;

		//�L����05�Ǎ��i��ʂɏo�́j
	case 'E':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[4];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[4];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		break;

		//�L����06�Ǎ��i��ʂɏo�́j
	case 'F':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[5];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[5];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		break;

		//�L����07�Ǎ��i��ʂɏo�́j
	case 'G':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[6];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[6];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		break;

		//�L����08�Ǎ��i��ʂɏo�́j
	case 'H':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[7];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[7];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		break;

		//�L����09�Ǎ��i��ʂɏo�́j
	case 'I':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[8];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[8];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		break;

		//�L����10�Ǎ��i��ʂɏo�́j
	case 'J':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[9];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[9];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		break;

		//�L����11�Ǎ��i��ʂɏo�́j
	case 'K':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[10];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[10];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		break;

		//�L����12�Ǎ��i��ʂɏo�́j
	case 'L':

		//�T�E���h�m�x�������̏���
		if (soundnovel_winownovel == 0) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[11];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		//�E�C���h�E�����̏���
		if (soundnovel_winownovel == 1) {
			//�w�i�摜��؂蔲���A�����G�̏�Ƀy�[�X�g
			CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

			CHARACTER = CHARACTER_LOAD[11];

			// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			CP++;
		}

		break;

		//********************�L�����N�^�[�摜�Ǎ�����(�����܂�)****************************************//

		//********************�w�i�摜�Ǎ�����(��������)****************************************//

		//�w�i01�Ǎ��i��ʂɏo�́j
	case 'M':

		BACKGROUND = BACKGROUND_LOAD[0];

		// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
		DrawGraph(0, 0, BACKGROUND, TRUE);

		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);
 			
			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}

		CP++;

		break;

		//�w�i02�Ǎ��i��ʂɏo�́j
	case 'N':

		BACKGROUND = BACKGROUND_LOAD[1];

		// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
		DrawGraph(0, 0, BACKGROUND, TRUE);

		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}

		CP++;

		break;

		//�w�i03�Ǎ��i��ʂɏo�́j
	case 'O':

		BACKGROUND = BACKGROUND_LOAD[2];

		// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//�w�i04�Ǎ��i��ʂɏo�́j
	case 'P':

		BACKGROUND = BACKGROUND_LOAD[3];

		// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//�w�i05�Ǎ��i��ʂɏo�́j
	case 'Q':

		BACKGROUND = BACKGROUND_LOAD[4];

		// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//�w�i06�Ǎ��i��ʂɏo�́j
	case 'R':

		BACKGROUND = BACKGROUND_LOAD[5];

		// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//�w�i07�Ǎ��i��ʂɏo�́j
	case 'S':

		BACKGROUND = BACKGROUND_LOAD[6];

		// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//�w�i08�Ǎ��i��ʂɏo�́j
	case 'T':

		BACKGROUND = BACKGROUND_LOAD[7];

		// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//�w�i09�Ǎ��i��ʂɏo�́j
	case 'U':

		BACKGROUND = BACKGROUND_LOAD[8];

		// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//�w�i10�Ǎ��i��ʂɏo�́j
	case 'V':

		BACKGROUND = BACKGROUND_LOAD[9];

		// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//�w�i11�Ǎ��i��ʂɏo�́j
	case 'W':

		BACKGROUND = BACKGROUND_LOAD[10];

		// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//�w�i12�Ǎ��i��ʂɏo�́j
	case 'X':

		BACKGROUND = BACKGROUND_LOAD[11];

		// �ǂ݂��񂾃O���t�B�b�N����ʍ���ɕ`��
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//********************�w�i�摜�Ǎ�����(�����܂�)****************************************//


		//********************BGM�Đ�����(��������)****************************************//

		//BGM01�Đ�����
	case 'Y':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[0];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM02�Đ�����
	case 'Z':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[1];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM03�Đ�����
	case 'a':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[2];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM04�Đ�����
	case 'b':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[3];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM05�Đ�����
	case 'c':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[4];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM06�Đ�����
	case 'd':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[5];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM07�Đ�����
	case 'e':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[6];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM08�Đ�����
	case 'f':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[7];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM09�Đ�����
	case 'g':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[8];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM10�Đ�����
	case 'h':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[9];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM11�Đ�����
	case 'i':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[10];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM12�Đ�����
	case 'j':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[11];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//********************BGM�Đ�����(�����܂�)****************************************//

		//********************SE�Đ�����(��������)****************************************//

		//SE01�Đ�����
	case 'k':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[0];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE02�Đ�����
	case 'l':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[1];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE03�Đ�����
	case 'm':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[2];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE04�Đ�����
	case 'n':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[3];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE05�Đ�����
	case 'o':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[4];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE06�Đ�����
	case 'p':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[5];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE07�Đ�����
	case 'q':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[6];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE08�Đ�����
	case 'r':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[7];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE09�Đ�����
	case 's':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[8];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE10�Đ�����
	case 't':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[9];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE11�Đ�����
	case 'u':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[10];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE12�Đ�����
	case 'v':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[11];

		// ���ʂ̐ݒ�
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//********************se�Đ�����(�����܂�)****************************************//

		//********************����Ǎ�����(��������)****************************************//

		//����01�Đ��i��ʂɓ�����Đ��j
	case 'w':

		//����01�Đ�
		PlayMovie("DATA/MOVIE/MOVIE01.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;

		break;

		//����02�Đ��i��ʂɓ�����Đ��j
	case 'x':

		//����02�Đ�
		PlayMovie("DATA/MOVIE/MOVIE02.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;

		break;

		//����01�Đ��i��ʂɓ�����Đ��j
	case 'y':

		//����01�Đ�
		PlayMovie("DATA/MOVIE/MOVIE03.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;

		break;

		//����02�Đ��i��ʂɓ�����Đ��j
	case 'z':

		//����02�Đ�
		PlayMovie("DATA/MOVIE/MOVIE04.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;

		break;

		//********************����Ǎ�����(�����܂�)****************************************//

	default:	// ���̑��̕���

				// �P�����������o��
		OneMojiBuf[0] = String[SP][CP];
		OneMojiBuf[1] = String[SP][CP + 1];
		OneMojiBuf[2] = '\0';

		if (soundnovel_winownovel == 1 && DrawPointY <= 399)
			DrawPointY = 400;

		if (soundnovel_winownovel == 0) {
			// �P�����`��
			DrawString(DrawPointX * MOJI_SIZE, DrawPointY * MOJI_SIZE, OneMojiBuf, GetColor(255, 255, 255));
		}

		if (soundnovel_winownovel == 1) {
			// �P�����`��
			DrawString(DrawPointX * MOJI_SIZE, DrawPointY, OneMojiBuf, GetColor(255, 255, 255));
		}

		// �Q�ƕ����ʒu���Q�o�C�g���߂�
		CP += 2;


		// �J�[�\�����ꕶ�����i�߂�
		DrawPointX++;

		//�X�L�b�v�E�I�[�g�ϐ����n�e�e�̏ꍇ
		if (skip_auto == 0) {
			// �����҂�
			WaitTimer(30 * STRING_SPEED / 100);
		}

		//�X�L�b�v�E�I�[�g�ϐ����n�m�̏ꍇ(�I�[�g���[�h)
		if (skip_auto == 1) {
			// �����҂�
			WaitTimer(30 * AUTO_SPEED / 100);
		}

		//�X�L�b�v�E�I�[�g�ϐ����n�m�̏ꍇ�i�X�L�b�v�j
		if (skip_auto == 2) {
			//��������
			WaitTimer(10 * SKIP_SPEED / 100);
		}

		// ��ʂ���͂ݏo������s����
		if (DrawPointX * MOJI_SIZE + MOJI_SIZE > 640)
			Kaigyou();

		//�T�E���h�m�x�������̉��y�[�W����
		if (soundnovel_winownovel == 0 && DrawPointY * MOJI_SIZE + MOJI_SIZE > CHARACTERY + MOJI_SIZE) {

			SetDrawScreen(DX_SCREEN_BACK);

			BACKLOG_COUNT++;

			if (BACKLOG_COUNT == 1) {

				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

			}

			if (BACKLOG_COUNT == 2) {

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

			}

			if (BACKLOG_COUNT == 3) {

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 4) {

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}
			
			if (BACKLOG_COUNT == 5) {

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 6) {

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 7) {

				BACKLOG_BACKGROUND = BACKLOG[5];

				BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 8) {

				BACKLOG_BACKGROUND = BACKLOG[6];

				BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[5];

				BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 9) {

				BACKLOG_BACKGROUND = BACKLOG[7];

				BACKLOG[8] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[6];

				BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[5];

				BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT >= 10) {

				BACKLOG_BACKGROUND = BACKLOG[8];

				BACKLOG[9] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[7];

				BACKLOG[8] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[6];

				BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[5];

				BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			SetDrawScreen(DX_SCREEN_FRONT);


			WaitTimer(300);
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;

			if (BACKGROUND != 0)
			DrawGraph(0, 0, BACKGROUND, TRUE);

			if (CHARACTER != 0)
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
		}

		//�E�C���h�E�����̉��y�[�W����
		if (soundnovel_winownovel == 1 && DrawPointY > 479 ) {


			SetDrawScreen(DX_SCREEN_BACK);

			BACKLOG_COUNT++;

			if (BACKLOG_COUNT == 1) {

				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

			}

			if (BACKLOG_COUNT == 2) {

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

			}

			if (BACKLOG_COUNT == 3) {

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 4) {

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 5) {

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 6) {

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 7) {

				BACKLOG_BACKGROUND = BACKLOG[5];

				BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 8) {

				BACKLOG_BACKGROUND = BACKLOG[6];

				BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[5];

				BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 9) {

				BACKLOG_BACKGROUND = BACKLOG[7];

				BACKLOG[8] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[6];

				BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[5];

				BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT >= 10) {

				BACKLOG_BACKGROUND = BACKLOG[8];

				BACKLOG[9] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[7];

				BACKLOG[8] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[6];

				BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[5];

				BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[4];

				BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[3];

				BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// ��ʂ����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			SetDrawScreen(DX_SCREEN_FRONT);


			WaitTimer(300);
			ClearDrawScreen();
			DrawPointY = 400;
			DrawPointX = 0;

			if (BACKGROUND != 0)
			DrawGraph(0, 0, BACKGROUND, TRUE);

			if (soundnovel_winownovel == 1) {

				int	Window_Color = GetColor(0, 0, 0);

				DrawBox(0, 400, 640, 480, Window_Color, TRUE);
			}

			if (CHARACTER != 0)
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
		}

		break;
	}

	return 0;
}

//������
int FORMAT() {

	// �`��ʒu�̏����ʒu�Z�b�g�i���j
	DrawPointX = 0;
	DrawPointY = 0;

	// �Q�ƕ����ʒu���Z�b�g
	SP = 0;	// �P�s�ڂ�
	CP = 0;	// �O����

	FileRead_close(ScriptFile);
	FileRead_close(Choice1);
	FileRead_close(Choice2);

	return 0;
}

//�X�N���[���V���b�g�@�\
int SCREENSHOT() {
	
		//�X�N���[���V���b�g�O�P�擾
		if (SCREENSHOT_COUNT == 0 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT01.png", 0);

			MessageBox(
				NULL,
				"�X�N���[���V���b�g�O�P���擾���܂����I",
				"�m�x���Q�[���G���W���uLINKS�v",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//�X�N���[���V���b�g�O�Q�擾
		if (SCREENSHOT_COUNT == 1 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT02.png", 0);

			MessageBox(
				NULL,
				"�X�N���[���V���b�g�O�Q���擾���܂����I",
				"�m�x���Q�[���G���W���uLINKS�v",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//�X�N���[���V���b�g�O�R�擾
		if (SCREENSHOT_COUNT == 2 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT03.png", 0);

			MessageBox(
				NULL,
				"�X�N���[���V���b�g�O�R���擾���܂����I",
				"�m�x���Q�[���G���W���uLINKS�v",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//�X�N���[���V���b�g�O�S�擾
		if (SCREENSHOT_COUNT == 3 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT04.png", 0);

			MessageBox(
				NULL,
				"�X�N���[���V���b�g�O�S���擾���܂����I",
				"�m�x���Q�[���G���W���uLINKS�v",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//�X�N���[���V���b�g�O�T�擾
		if (SCREENSHOT_COUNT == 4 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT05.png", 0);

			MessageBox(
				NULL,
				"�X�N���[���V���b�g�O�T���擾���܂����I",
				"�m�x���Q�[���G���W���uLINKS�v",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//�X�N���[���V���b�g�O�U�擾
		if (SCREENSHOT_COUNT == 5 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT06.png", 0);

			MessageBox(
				NULL,
				"�X�N���[���V���b�g�O�U���擾���܂����I",
				"�m�x���Q�[���G���W���uLINKS�v",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//�X�N���[���V���b�g�O�V�擾
		if (SCREENSHOT_COUNT == 6 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT07.png", 0);

			MessageBox(
				NULL,
				"�X�N���[���V���b�g�O�V���擾���܂����I",
				"�m�x���Q�[���G���W���uLINKS�v",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//�X�N���[���V���b�g�O�W�擾
		if (SCREENSHOT_COUNT == 7 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT08.png", 0);

			MessageBox(
				NULL,
				"�X�N���[���V���b�g�O�W���擾���܂����I",
				"�m�x���Q�[���G���W���uLINKS�v",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//�X�N���[���V���b�g�O�X�擾
		if (SCREENSHOT_COUNT == 8 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT09.png", 0);

			MessageBox(
				NULL,
				"�X�N���[���V���b�g�O�X���擾���܂����I",
				"�m�x���Q�[���G���W���uLINKS�v",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//�X�N���[���V���b�g�P�O�擾
		if (SCREENSHOT_COUNT == 9 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT10.png", 0);

			MessageBox(
				NULL,
				"�X�N���[���V���b�g�P�O���擾���܂����I",
				"�m�x���Q�[���G���W���uLINKS�v",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//�X�N���[���V���b�g�擾���E���b�Z�[�W
		if (SCREENSHOT_COUNT >= 10 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			MessageBox(
				NULL,
				"����ȏ�X�N���[���V���b�g���擾�ł��܂���",
				"�m�x���Q�[���G���W���uLINKS�v",
				MB_OK
			);

			WaitTimer(300);

		}

	return 0;
		
}

//�R���t�B�O(�^�C�g�����)
int CONFIG(){


	SAVE = MessageBox(
		NULL,
		"�ݒ��ύX���܂����H",
		"�m�x���Q�[���G���W���uLINKS�v",
		MB_YESNO
	);

	if (SAVE == IDYES) {

		Config = 1;

		GAME_y = GAMEMENU_y;

		ClearDrawScreen();

		WaitTimer(300);

		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && Config == 1) {

			GAME_MENU_CURSOR(Cr, GAME_y);

			//�Z�[�u�f�[�^���`��
			DrawString(SAVE_NAME_X, GAMEMENU_y, "�a�f�l����", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 2, "�r�d����", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 3, "�I�[�g���x", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 4, "�X�L�b�v���x", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 5, "�����`�摬�x", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 6, "�`����@", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 7, "��A�N�e�B�u��", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 8, "���j���[�ɖ߂�", Cr);

			//�ڐ���`��

			if (BGM_VOL_COUNT == 10)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "��������������������", Cr);

			if (BGM_VOL_COUNT == 9)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "������������������", Cr);

			if (BGM_VOL_COUNT == 8)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "����������������", Cr);

			if (BGM_VOL_COUNT == 7)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "��������������", Cr);

			if (BGM_VOL_COUNT == 6)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "������������", Cr);

			if (BGM_VOL_COUNT == 5)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "����������", Cr);

			if (BGM_VOL_COUNT == 4)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "��������", Cr);

			if (BGM_VOL_COUNT == 3)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "������", Cr);

			if (BGM_VOL_COUNT == 2)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "����", Cr);

			if (BGM_VOL_COUNT == 1)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "��", Cr);

			if (BGM_VOL_COUNT == 0)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "", Cr);

			if (SE_VOL_COUNT == 10)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "��������������������", Cr);

			if (SE_VOL_COUNT == 9)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "������������������", Cr);

			if (SE_VOL_COUNT == 8)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "����������������", Cr);

			if (SE_VOL_COUNT == 7)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "��������������", Cr);

			if (SE_VOL_COUNT == 6)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "������������", Cr);

			if (SE_VOL_COUNT == 5)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "����������", Cr);

			if (SE_VOL_COUNT == 4)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "��������", Cr);

			if (SE_VOL_COUNT == 3)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "������", Cr);

			if (SE_VOL_COUNT == 2)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "����", Cr);

			if (SE_VOL_COUNT == 1)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "��", Cr);

			if (SE_VOL_COUNT == 0)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "", Cr);

			if (AUTO_SPEED_COUNT == 10)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "��������������������", Cr);

			if (AUTO_SPEED_COUNT == 9)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "������������������", Cr);

			if (AUTO_SPEED_COUNT == 8)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "����������������", Cr);

			if (AUTO_SPEED_COUNT == 7)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "��������������", Cr);

			if (AUTO_SPEED_COUNT == 6)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "������������", Cr);

			if (AUTO_SPEED_COUNT == 5)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "����������", Cr);

			if (AUTO_SPEED_COUNT == 4)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "��������", Cr);

			if (AUTO_SPEED_COUNT == 3)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "������", Cr);

			if (AUTO_SPEED_COUNT == 2)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "����", Cr);

			if (AUTO_SPEED_COUNT == 1)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "��", Cr);

			if (AUTO_SPEED_COUNT == 0)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "", Cr);

			if (SKIP_SPEED_COUNT == 10)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "��������������������", Cr);

			if (SKIP_SPEED_COUNT == 9)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "������������������", Cr);

			if (SKIP_SPEED_COUNT == 8)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "����������������", Cr);

			if (SKIP_SPEED_COUNT == 7)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "��������������", Cr);

			if (SKIP_SPEED_COUNT == 6)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "������������", Cr);

			if (SKIP_SPEED_COUNT == 5)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "����������", Cr);

			if (SKIP_SPEED_COUNT == 4)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "��������", Cr);

			if (SKIP_SPEED_COUNT == 3)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "������", Cr);

			if (SKIP_SPEED_COUNT == 2)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "����", Cr);

			if (SKIP_SPEED_COUNT == 1)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "��", Cr);

			if (SKIP_SPEED_COUNT == 0)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "", Cr);

			if (STRING_SPEED_COUNT == 10)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "��������������������", Cr);

			if (STRING_SPEED_COUNT == 9)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "������������������", Cr);

			if (STRING_SPEED_COUNT == 8)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "����������������", Cr);

			if (STRING_SPEED_COUNT == 7)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "��������������", Cr);

			if (STRING_SPEED_COUNT == 6)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "������������", Cr);

			if (STRING_SPEED_COUNT == 5)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "����������", Cr);

			if (STRING_SPEED_COUNT == 4)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "��������", Cr);

			if (STRING_SPEED_COUNT == 3)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "������", Cr);

			if (STRING_SPEED_COUNT == 2)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "����", Cr);

			if (STRING_SPEED_COUNT == 1)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "��", Cr);

			if (STRING_SPEED_COUNT == 0)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "", Cr);

			if (soundnovel_winownovel == 0)
				DrawString(SAVE_NAME_X + CURSOR * 6, GAMEMENU_y * 6, "�T�E���h�m�x����", Cr);

			if (soundnovel_winownovel == 1)
				DrawString(SAVE_NAME_X + CURSOR * 6, GAMEMENU_y * 6, "�E�C���h�E��", Cr);

			if (WindowActive == TRUE)
				DrawString(SAVE_NAME_X + CURSOR * 7, GAMEMENU_y * 7, "����", Cr);

			if (WindowActive == FALSE)
				DrawString(SAVE_NAME_X + CURSOR * 7, GAMEMENU_y * 7, "������", Cr);

			//�a�f�l���ʒ���
			if (GAME_y == GAMEMENU_y && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				WaitTimer(300);

				BGM_VOL += 10;
				BGM_VOL_COUNT += 1;

				if (BGM_VOL_COUNT >= 10) {
					BGM_VOL = 100;
					BGM_VOL_COUNT = 10;
				}
			}

			if (GAME_y == GAMEMENU_y && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

				WaitTimer(300);

				BGM_VOL -= 10;
				BGM_VOL_COUNT -= 1;

				if (BGM_VOL_COUNT <= 0) {
					BGM_VOL = 0;
					BGM_VOL_COUNT = 0;
				}
			}

			//�r�d���ʒ���
			if (GAME_y == GAMEMENU_y * 2 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 2 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				WaitTimer(300);

				SE_VOL += 10;
				SE_VOL_COUNT += 1;

				if (SE_VOL_COUNT >= 10) {
					SE_VOL = 100;
					SE_VOL_COUNT = 10;
				}
			}

			if (GAME_y == GAMEMENU_y * 2 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 2 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

				WaitTimer(300);

				SE_VOL -= 10;
				SE_VOL_COUNT -= 1;

				if (SE_VOL_COUNT <= 0) {
					SE_VOL = 0;
					SE_VOL_COUNT = 0;
				}
			}

			//�I�[�g���x����
			if (GAME_y == GAMEMENU_y * 3 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 3 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				WaitTimer(300);

				AUTO_SPEED += 10;
				AUTO_SPEED_COUNT += 1;

				if (AUTO_SPEED_COUNT >= 10) {
					AUTO_SPEED = 100;
					AUTO_SPEED_COUNT = 10;
				}
			}

			if (GAME_y == GAMEMENU_y * 3 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 3 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

				WaitTimer(300);

				AUTO_SPEED -= 10;
				AUTO_SPEED_COUNT -= 1;

				if (AUTO_SPEED_COUNT <= 0) {
					AUTO_SPEED = 0;
					AUTO_SPEED_COUNT = 0;
				}
			}

			//�X�L�b�v���x����
			if (GAME_y == GAMEMENU_y * 4 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 4 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				WaitTimer(300);

				SKIP_SPEED += 10;
				SKIP_SPEED_COUNT += 1;

				if (SKIP_SPEED_COUNT >= 10) {
					SKIP_SPEED = 100;
					SKIP_SPEED_COUNT = 10;
				}
			}

			if (GAME_y == GAMEMENU_y * 4 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 4 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

				WaitTimer(300);

				SKIP_SPEED -= 10;
				SKIP_SPEED_COUNT -= 1;

				if (SKIP_SPEED_COUNT <= 0) {
					SKIP_SPEED = 0;
					SKIP_SPEED_COUNT = 0;
				}

			}

			//�����`�摬�x����
			if (GAME_y == GAMEMENU_y * 5 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 5 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				WaitTimer(300);

				STRING_SPEED += 10;
				STRING_SPEED_COUNT += 1;

				if (STRING_SPEED_COUNT >= 10) {
					STRING_SPEED = 100;
					STRING_SPEED_COUNT = 10;
				}
			}

			if (GAME_y == GAMEMENU_y * 5 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 5 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

				WaitTimer(300);

				STRING_SPEED -= 10;
				STRING_SPEED_COUNT -= 1;

				if (STRING_SPEED_COUNT <= 0) {
					STRING_SPEED = 0;
					STRING_SPEED_COUNT = 0;
				}

			}

			//�T�E���h�m�x�����ƃE�C���h�E���̐؂�ւ�
			if (GAME_y == GAMEMENU_y * 6 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 6 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				WaitTimer(300);
				soundnovel_winownovel = 0;
			}

			if (GAME_y == GAMEMENU_y * 6 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 6 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

				WaitTimer(300);
				soundnovel_winownovel = 1;
			}

			//��A�N�e�B�u���̏����̐؂�ւ�
			if (GAME_y == GAMEMENU_y * 7 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 7 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				WaitTimer(300);
				WindowActive = FALSE;

				//��A�N�e�B�u��Ԃł̓Q�[�������s���Ȃ�
				SetAlwaysRunFlag(WindowActive);
			}

			if (GAME_y == GAMEMENU_y * 7 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 7 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

				WaitTimer(300);
				WindowActive = TRUE;

				//��A�N�e�B�u��Ԃł��Q�[�������s
				SetAlwaysRunFlag(WindowActive);
			}

			//�^�C�g���ɖ߂�
			if (GAME_y == GAMEMENU_y * 8 && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == GAMEMENU_y * 8 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"�^�C�g���ɖ߂�܂����H",
					"�Q�[�������N�X����̃m�x���Q�[���G���W���uLINKS�v",
					MB_YESNO
				);

				if (SAVE == IDYES) {
					WaitTimer(300);
					ClearDrawScreen();
					GAME_y = GAMEMENU_y;
					Config = 0;
					break;
				}

				WaitTimer(300);
			}

			//�L�[����֘A
			SetDrawScreen(DX_SCREEN_BACK);

			ClearDrawScreen();

			//�}�E�X����֘A
			Mouse_Move();

			//�L�[����֘A
			if (Key[KEY_INPUT_DOWN] == 1) {
				ClearDrawScreen();
				GAME_y += GAMEMENU_y;
				if (GAME_y == (GAMEMENU_y * 9))
					GAME_y = GAMEMENU_y;
			}

			if (Key[KEY_INPUT_UP] == 1) {
				ClearDrawScreen();
				GAME_y -= GAMEMENU_y;
				if (GAME_y == (GAMEMENU_y - GAMEMENU_y))
					GAME_y = (GAMEMENU_y * 8);
			}

			SetDrawScreen(DX_SCREEN_FRONT);


		}
	}

	WaitTimer(300);



	return 0;
}

//�t���X�N���[��/�E�C���h�E�؂�ւ�
//int WindowChange_full_window() {

//	if (CheckHitKey(KEY_INPUT_F11) == 1 && GetWindowModeFlag() == TRUE) {
//		MATERIAL_LOAD();
//		ChangeWindowMode(FALSE);
//	}
//
