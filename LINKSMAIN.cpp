//�Q�[�������N�X�J�� �ȈՃm�x���Q�[���G���W���u�k�h�m�j�r�vver2.80
#include "DxLib.h"
#include "stdio.h"
#include "GAME.h"
#include "DEF.h"
#include "resource.h"

// ������`��̈ʒu
extern int DrawPointX, DrawPointY;

// �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^
extern int SP, CP;

//�X�N���v�g�Ǎ��ϐ�
extern int ScriptFile;

//�X�N���v�g�p�Ǎ��z��
extern char String[GYOU][RETU];

//�^�C�g���֘A
extern int TITLE;
extern unsigned int Cr;

//�G���h�t���O
extern int EndFlag;

//���ǃX�L�b�v�ϐ�
extern int LINKS;
extern int A;
extern int B;
extern int C;
extern int D;
extern int E;
extern int F;
extern int G;
extern int H;
extern int I;
extern int J;
extern int K;
extern int L;
extern int M;
extern int N;

//�ݒ�p�ϐ�
extern int BGM_VOL;
extern int SE_VOL;
extern int BGM_VOL_COUNT;
extern int SE_VOL_COUNT;

//�o�b�N���O�ϐ�
extern char *BACKLOG_DELETE;

//�Z�[�u�p�ϐ�
extern int SAVE, SAVE_CHOICE;
extern char *SAVESNAP_CHOICE_DELETE;

//�X�L�b�v�E�I�[�g���[�h�p�ϐ�
extern int skip_auto;
extern int SKIP_SPEED;
extern int SKIP_SPEED_COUNT;
extern int AUTO_SPEED;
extern int AUTO_SPEED_COUNT;

//�L�[����
extern int Key[256];
extern int y;
extern int SAVE_y;
extern int GAME_y;

//DX���C�u�����������O����
void DXLib_PREP() {

	//���O�̒��o
	SetOutApplicationLogValidFlag(FALSE);

	//�A�C�R��
	SetWindowIconID(101);

	//�E�C���h�E�ɕ\�������Q�[���\�t�g��
	SetWindowText("�m�x���Q�[���G���W���uLINKS�v");

	//�E�C���h�E�����R�ɕύX�ł���
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);

	//�E�C���h�E�`��̎��
	SetDrawMode(DX_DRAWMODE_NEAREST);

	//�E�C���h�E�̎��
	SetWindowStyleMode(7);

	//�����E�C���h�E�T�C�Y
	SetWindowSize(640, 480);

	//�E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);
}

//DX���C�u�����������㏈��
void DXLib_POST_PREP() {

	//�}�E�X�`��ݒ�
	SetMouseDispFlag(TRUE);

	//DX�A�[�J�C�u�@�\�̎g�p
	SetUseDXArchiveFlag(TRUE);

	//�e�f�ރf�[�^�Ǎ�
	MATERIAL_LOAD();

	// �t�H���g�̃T�C�Y�Z�b�g
	SetFontSize(MOJI_SIZE);

	//�t�H���g�̐ݒ�
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//�Q�[�������N�X���S�\��
	PlayMovie("DATA/MOVIE/OP.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);

	//OP��ʂ̍폜
	ClearDrawScreen();
	WaitTimer(600);

	//�ݒ�̓Ǎ�
	CONFIG_LOAD();
}

//�^�C�g�����j���[(�L�[����)
void TITLE_MENU_KEY_MOVE() {

	if (Key[KEY_INPUT_DOWN] == 1) {
		y += CURSOR;
		if (y == (GAMEQUIT + CURSOR))
			y = GAMESTART;
	}

	if (Key[KEY_INPUT_UP] == 1) {
		y -= CURSOR;
		if (y == (GAMESTART - CURSOR))
			y = GAMEQUIT;
	}
}

//�^�C�g�����j���[�I������
void TITLE_MENU_END() {

	SAVE = MessageBox(
		NULL,
		"�I�����܂����H",
		"�m�x���Q�[���G���W���uLINKS�v",
		MB_YESNO
	);

	if (SAVE == IDYES)
		EndFlag = 99999;

	WaitTimer(300);
}

//�^�C�g�����j���[(�I������)
void TITLE_MENU_CHOICE() {

	if (y == GAMESTART && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == GAMESTART && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		EndFlag = 1;

	if (y == GAMELOAD && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == GAMELOAD && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		SAVEDATA_LOAD();

	if (y == GAMECONFIG && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == GAMECONFIG && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		CONFIG();

	if (y == QUICKLOAD && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == QUICKLOAD && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		QUICKSAVE_LOAD();

	if (y == GAMEQUIT && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == GAMEQUIT && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		TITLE_MENU_END();
}

//�^�C�g�����j���[�֐�
void TITLE_MENU() {

	//�^�C�g�����j���[
	if (EndFlag == 99) {

		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && EndFlag == 99) {

			//�^�C�g���\��
			DrawGraph(0, 0, TITLE, TRUE);

			//�^�C�g�����j���[�\��
			title(Cr, y);

			//�X�N���[���V���b�g�@�\
			SCREENSHOT();

			//�}�E�X����
			Mouse_Move();

			//�L�[����֘A
			TITLE_MENU_KEY_MOVE();

			//��ʃN���A����
			SCREEN_CLEAR();

			//�^�C�g�����j���[(�I������)
			TITLE_MENU_CHOICE();

			//�I���E�C���h�E
			GAME_FINISH();
		}
	}
}

//�Q�ƕ����񏈗�
void WORD_FORMAT() {

	// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
	if (String[SP][CP] == '\0')
	{
		SP++;
		CP = 0;
	}
}

//�Q�[���̃��[�v(LINKS)
void GAME_LOOP_LINKS() {

	//���C�����[�g
	if (EndFlag == 1) {

		if (LINKS == 0)
			skip_auto = 0;

		//���C���X�N���v�g�Ǎ�
		SCRIPT_READ();

		//���C�����[�v(LINKS)
		while (EndFlag != 99 && ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��1�łȂ�������I������B
			if (EndFlag != 1 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				LINKS = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(A)
void GAME_LOOP_A() {

	//A���[�g
	if (EndFlag == 2) {

		if (A == 0)
			skip_auto = 0;

		//A���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//�`���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��2�łȂ�������I������
			if (EndFlag != 2 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				A = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(B)
void GAME_LOOP_B() {

	//B���[�g
	if (EndFlag == 3) {

		if (B == 0)
			skip_auto = 0;

		//B���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//B���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��3�łȂ�������I������
			if (EndFlag != 3 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				B = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(C)
void GAME_LOOP_C() {

	//C���[�g
	if (EndFlag == 4) {

		if (C == 0)
			skip_auto = 0;

		//C���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//C���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��4�łȂ�������I������
			if (EndFlag != 4 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				C = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(D)
void GAME_LOOP_D() {

	//D���[�g
	if (EndFlag == 5) {

		if (D == 0)
			skip_auto = 0;

		//D���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//D���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��5�łȂ�������I������
			if (EndFlag != 5 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				D = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(E)
void GAME_LOOP_E() {

	//E���[�g
	if (EndFlag == 6) {

		if (E == 0)
			skip_auto = 0;

		//E���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//E���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��2�łȂ�������I������
			if (EndFlag != 6 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				E = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(F)
void GAME_LOOP_F() {

	//F���[�g
	if (EndFlag == 7) {

		if (F == 0)
			skip_auto = 0;

		//F���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//F���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��7�łȂ�������I������
			if (EndFlag != 7 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				F = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(G)
void GAME_LOOP_G() {

	//G���[�g
	if (EndFlag == 8) {

		if (G == 0)
			skip_auto = 0;

		//G���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//G���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��7�łȂ�������I������
			if (EndFlag != 8) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(H)
void GAME_LOOP_H() {

	//H���[�g
	if (EndFlag == 9) {

		if (H == 0)
			skip_auto = 0;

		//H���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//H���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��7�łȂ�������I������
			if (EndFlag != 9) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(I)
void GAME_LOOP_I() {

	//I���[�g
	if (EndFlag == 10) {

		if (I == 0)
			skip_auto = 0;

		//I���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//I���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��7�łȂ�������I������
			if (EndFlag != 10) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(J)
void GAME_LOOP_J() {

	//J���[�g
	if (EndFlag == 11) {

		if (J == 0)
			skip_auto = 0;

		//J���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//J���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��7�łȂ�������I������
			if (EndFlag != 11) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(K)
void GAME_LOOP_K() {

	//K���[�g
	if (EndFlag == 12) {

		if (K == 0)
			skip_auto = 0;

		//K���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//K���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��7�łȂ�������I������
			if (EndFlag != 12) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(L)
void GAME_LOOP_L() {

	//L���[�g
	if (EndFlag == 13) {

		if (L == 0)
			skip_auto = 0;

		//L���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//L���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��7�łȂ�������I������
			if (EndFlag != 13) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(M)
void GAME_LOOP_M() {

	//M���[�g
	if (EndFlag == 14) {

		if (M == 0)
			skip_auto = 0;

		//M���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//M���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��7�łȂ�������I������
			if (EndFlag != 14) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v(N)
void GAME_LOOP_N() {

	//N���[�g
	if (EndFlag == 15) {

		if (N == 0)
			skip_auto = 0;

		//N���[�g�X�N���v�g�Ǎ�
		SCRIPT_READ();

		//N���[�g���[�v
		while (ProcessMessage() == 0)
		{
			//�^�O����
			SCRIPT_OUTPUT();

			//�Q�[�����j���[
			GAMEMENU();

			//�X�N���[���V���b�g�擾
			SCREENSHOT();

			//�V���[�g�J�b�g�L�[
			SHORTCUT_KEY();

			//�I��
			GAME_FINISH();

			// �I���t���O��7�łȂ�������I������
			if (EndFlag != 15) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//�Q�ƕ����񏈗�
			WORD_FORMAT();
		}
	}
}

//�Q�[���̃��[�v
void GAME_LOOP() {

	//�Q�[���̃��[�v(LINKS)
	GAME_LOOP_LINKS();
	
	//�Q�[���̃��[�v(A)
	GAME_LOOP_A();

	//�Q�[���̃��[�v(B)
	GAME_LOOP_B();

	//�Q�[���̃��[�v(C)
	GAME_LOOP_C();

	//�Q�[���̃��[�v(D)
	GAME_LOOP_D();

	//�Q�[���̃��[�v(E)
	GAME_LOOP_E();

	//�Q�[���̃��[�v(F)
	GAME_LOOP_F();

	//�Q�[���̃��[�v(G)
	GAME_LOOP_G();

	//�Q�[���̃��[�v(H)
	GAME_LOOP_H();

	//�Q�[���̃��[�v(I)
	GAME_LOOP_I();

	//�Q�[���̃��[�v(J)
	GAME_LOOP_J();

	//�Q�[���̃��[�v(K)
	GAME_LOOP_K();

	//�Q�[���̃��[�v(L)
	GAME_LOOP_L();

	//�Q�[���̃��[�v(M)
	GAME_LOOP_M();

	//�Q�[���̃��[�v(N)
	GAME_LOOP_N();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//DX���C�u�����������O����
	DXLib_PREP();

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)	
	{
		// �G���[���N�����璼���ɏI��
		return -1;
	}

	//DX���C�u�����������㏈��
	DXLib_POST_PREP();

	while (ProcessMessage() == 0 && EndFlag != 99999) {

		//�^�C�g�����j���[
		TITLE_MENU();

		//�e��Q�[�����[�v
		GAME_LOOP();
	}

	//�ݒ�̕ۑ�
	CONFIG_SAVE();

	//�o�b�N���O�摜�̍폜
	BACKLOG_DELETE = "DATA/BACKLOG/BACKLOG1.png";
	remove(BACKLOG_DELETE);

	//�I�����Z�[�u�X�i�b�v�폜
	SAVESNAP_CHOICE_DELETE = "DATA/SAVE/SAVESNAP_CHOICE.png";
	remove(SAVESNAP_CHOICE_DELETE);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}