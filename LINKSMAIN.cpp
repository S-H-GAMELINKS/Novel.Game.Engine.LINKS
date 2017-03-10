//�Q�[�������N�X�J�� �ȈՃm�x���Q�[���G���W���u�k�h�m�j�r�v
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
extern int SaveFlag;
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
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

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)	
	{
		// �G���[���N�����璼���ɏI��
		return -1;
	}

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

	while (ProcessMessage() == 0 && EndFlag != 99999) {
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
				SetDrawScreen(DX_SCREEN_BACK);

				if (Key[KEY_INPUT_DOWN] == 1) {
					ClearDrawScreen();
					y += CURSOR;
					if (y == (GAMEQUIT + CURSOR))
						y = GAMESTART;
				}

				if (Key[KEY_INPUT_UP] == 1) {
					ClearDrawScreen();
					y -= CURSOR;
					if (y == (GAMESTART - CURSOR))
						y = GAMEQUIT;
				}

				SetDrawScreen(DX_SCREEN_FRONT);

				if (y == GAMESTART && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == GAMESTART && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
					EndFlag = 1;
					break;
				}

				if (y == GAMELOAD && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == GAMELOAD && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
					ClearDrawScreen();
					SaveFlag = 2;
					SAVEDATA_LOAD();
					break;
				}

				if (y == GAMECONFIG && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == GAMECONFIG && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
					ClearDrawScreen();
					CONFIG();
					break;
				}

				if (y == QUICKLOAD && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == QUICKLOAD && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
					ClearDrawScreen();
					QUICKSAVE_LOAD();
					break;
				}

				if (y == GAMEQUIT && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == GAMEQUIT && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

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

		//���C�����[�g
		if (EndFlag == 1) {

			if (LINKS == 0)
				skip_auto = 0;

			//���C���X�N���v�g�Ǎ�
			SCRIPT_READ();

			//���C�����[�v(LINKS)
			while (ProcessMessage() == 0)
			{
				//�^�O����
				SCRIPT_OUTPUT();

				//�Q�[�����j���[
				GAMEMENU();

				//�X�N���[���V���b�g�擾
				SCREENSHOT();

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

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				//�I��
				GAME_FINISH();

				// �I���t���O��2�łȂ�������I������
				if (EndFlag != 2 && EndFlag != 99999 ) {

					if (SAVE_CHOICE == 0)
						FORMAT();
	
					A = 1;
					SKIP_READ_SAVE();
					break;
				}

				if (EndFlag == 99999)
					break;

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				//�I��
				GAME_FINISH();

				// �I���t���O��7�łȂ�������I������
				if (EndFlag != 8) {

					if (SAVE_CHOICE == 0)
						FORMAT();
					
					break;
				}

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				//�I��
				GAME_FINISH();

				// �I���t���O��7�łȂ�������I������
				if (EndFlag != 9) {

					if (SAVE_CHOICE == 0)
						FORMAT();
	
					break;
				}

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				//�I��
				GAME_FINISH();

				// �I���t���O��7�łȂ�������I������
				if (EndFlag != 10) {
					
					if (SAVE_CHOICE == 0)
						FORMAT();
					
					break;
				}

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				//�I��
				GAME_FINISH();

				// �I���t���O��7�łȂ�������I������
				if (EndFlag != 11) {
					
					if (SAVE_CHOICE == 0)
						FORMAT();
	
					break;
				}

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				//�I��
				GAME_FINISH();

				// �I���t���O��7�łȂ�������I������
				if (EndFlag != 12) {

					if (SAVE_CHOICE == 0)
						FORMAT();

					break;
				}

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				//�I��
				GAME_FINISH();

				// �I���t���O��7�łȂ�������I������
				if (EndFlag != 13) {

					if (SAVE_CHOICE == 0)
						FORMAT();

					break;
				}

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				//�I��
				GAME_FINISH();

				// �I���t���O��7�łȂ�������I������
				if (EndFlag != 14) {

					if (SAVE_CHOICE == 0)
						FORMAT();
				
					break;
				}

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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

				//�I��
				GAME_FINISH();

				// �I���t���O��7�łȂ�������I������
				if (EndFlag != 15) {
					
					if (SAVE_CHOICE == 0)
						FORMAT();

					break;
				}

				// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
				if (String[SP][CP] == '\0')
				{
					SP++;
					CP = 0;
				}
			}
		}

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