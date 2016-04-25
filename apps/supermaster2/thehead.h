/* SuperMaster
written by Jared Bruni
www.LostSideDead.com

  "Open Source, Open Mind"
  
	
*/

/* FREESTYLE */

#define Sync if(mxhwnd.SyncChange()) 
#include"masterx.h"
#include<fstream>

using namespace std;

extern MasterXHWND mxhwnd;



// function prototypes
inline void GetPointFromPos(int pos,int& x, int& y);
int getoff_set();
void scrollleft();
void scrollright();
void releaseparticle(int pos, int type,bool dir);
void newgame();
void load_level(char* level);
void setcredits();



int cur_level = 0;
int score = 0;
int kills = 0;
int lives = 0;


class Intro : public MasterGameObject
{
public:
	
	virtual void load()
	{
		mxhwnd.LoadGraphic(&logo,"logo.bmp");
		mxhwnd.LoadSound(&sintro,"open.wav");
		play = false;
	}
	
	virtual void update()
	{
		if(play == false)
		{
			play = true;
			sintro.Play();
		}
		draw();
		logic();
	}
	
	
private:
	bool play;
	
	inline void draw()
	{
		logo.DisplayGraphic(0,0);
	}
	
	inline void logic()
	{
		static int wait = 0;
		
		mxhwnd.text.sprinttext(0,0,"Loading %d", wait);
			

		if(++wait > 150)
		{
			wait = 0;
			mxhwnd.SetScreen(ID_START);
		}
	}
	
	MasterGraphic logo;
	MasterSound   sintro;
};



class Start : public MasterGameObject
{
public:
	
	MASTERSCREEN screen;
	enum { ID_STARTSCREEN, ID_ABOUTSCREEN = 1 };
	
	virtual void load()
	{
		icon[0].SetColorKey(RGB(255,255,255));
		icon[1].SetColorKey(RGB(255,255,255));
		icon[2].SetColorKey(RGB(255,255,255));
		icon[3].SetColorKey(RGB(255,255,255));
		
		img[0].SetColorKey(RGB(255,255,255));
		img[1].SetColorKey(RGB(255,255,255));
		
		mxhwnd.LoadGraphic(&startlogo,"start.bmp");
		mxhwnd.LoadGraphic(&icon[0],"icon.bmp");
		mxhwnd.LoadGraphic(&icon[1],"icon1.bmp");
		mxhwnd.LoadGraphic(&icon[2],"icon2.bmp");
		mxhwnd.LoadGraphic(&icon[3],"icon3.bmp");
		mxhwnd.LoadGraphic(&img[0],"xhero.bmp");
		mxhwnd.LoadGraphic(&img[1],"xgrandma.bmp");
		
		
		screen = ID_STARTSCREEN;
		cursor_pos = 0;
		cur_icon = 0;
		icon_dir = true;
		credits.load();
	}
	
	virtual void update()
	{
		draw();
		logic();
	}
	
	inline void keypress(int key)
	{
		switch(screen)
		{
		case ID_STARTSCREEN:
			{
				switch(key)
				{
				case VK_DOWN:
					if(cursor_pos < 2)
						cursor_pos++;
					break;
				case VK_UP:
					if(cursor_pos > 0)
						cursor_pos--;
					
					break;
				case VK_RETURN:
					{
						switch(cursor_pos)
						{
						case 0:
							newgame();
							mxhwnd.SetScreen(ID_LAUNCH);
							break;
						case 1:
							screen = ID_ABOUTSCREEN;
							break;
						case 2:
							mxhwnd.Kill();
							break;
						}
					}
					break;
				}
			}
			break;
		case ID_ABOUTSCREEN:
			{
				switch(key)
				{
				case VK_RETURN:
					screen = ID_STARTSCREEN;
					break;
				}
			}
			break;
		}
	}
	
private:
	
	int cursor_pos;
	int icon_x,icon_y;
	int cur_icon;
	bool icon_dir;
	
	inline void draw()
	{
		startlogo.DisplayGraphic(0,0);
		img[0].DisplayGraphic(50,100);
		img[1].DisplayGraphic(350,170);
		
		switch(screen)
		{
		case ID_STARTSCREEN:
			{
				
				switch(cursor_pos)
				{
				case 0:
					{
						icon_x = 90;
						icon_y = 110;
					}
					break;
				case 1:
					{
						icon_x = 90;
						icon_y = 150;
					}
					break;
				case 2:
					{
						icon_x = 90;
						icon_y = 200;
					}
					break;
				}
				
				icon[cur_icon].DisplayGraphic(icon_x,icon_y);
				
			}
			break;
		case ID_ABOUTSCREEN:
			{
				mxhwnd.paint.mxdrawrect(10,170,480,270,0x0,0x0);
				mxhwnd.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
				mxhwnd.text.printtext("[press enter to return]",20,180);
				credits.update();
			}
			break;
		}
	}
	
	inline void logic()
	{
		switch(screen)
		{
		case ID_STARTSCREEN:
			{
				if(icon_dir == true)
				{
					cur_icon ++;
					if(cur_icon >= 3)
					{
						cur_icon = 2;
						icon_dir = false;
					}
				}
				else
				{
					cur_icon--;
					if(cur_icon < 0)
					{
						cur_icon = 0;
						icon_dir = true;
					}
				}
			}
			break;
		}
	}
	
	MasterGraphic startlogo;
	MasterGraphic icon[4];
	MasterGraphic img[2];
	
	class Credits : public MasterGameObject
	{
	public:
		
		
		virtual void load()
		{
			credit_off = 0;
			credits[0].set("SuperMaster - coded by Jared Bruni",RGB(255,0,0));
			credits[1].set("Tested by Tek ",RGB(255,0,0));
			credits[2].set("",RGB(255,0,0));
			credits[3].set("Shout Outs To",RGB(255,255,255));
			credits[4].set("Consumnes River College",RGB(0,255,255));
			credits[5].set("PlanetSourceCode.com",RGB(255,0,0));
			credits[6].set("LostSideDead & its members",RGB(0,0,255));
			credits[7].set("Nintendo for inspiring my dreams as a child",RGB(255,0,0));
			credits[8].set("Johnathan Parker PHD for his meditaiton tapes",RGB(255,0,0));
			credits[9].set("",RGB(255,0,0));
			credits[10].set("",RGB(255,0,0));
			credits[11].set("Super Master Written Utilizing MasterX SDK",RGB(255,0,0));
			credits[12].set("This Program is Completly free",RGB(255,0,0));
			credits[13].set("you have permission to post it on your sites",RGB(255,0,0));
			credits[14].set("play with it, change the code around",RGB(255,0,0));
			credits[15].set("or do whatever you see fit",RGB(255,0,0));
			credits[16].set("",RGB(255,0,0));
			credits[17].set("",RGB(255,0,0));
			credits[18].set("",RGB(255,0,0));
			credits[19].set("",RGB(255,0,0));
			credits[20].set("",RGB(255,0,0));
			credits[21].set("Open Source, Open Mind",RGB(255,255,255));
			credits[22].set("be sure to check out www.LostSideDead.com",RGB(0,255,0));
			credits[23].set("A beautiful MasterPeace",RGB(255,0,0));
			credits[24].set("(-<) the end :)",RGB(255,0,0));
			credits[26].set("",RGB(255,0,0));
			credits[27].set("",RGB(255,0,0));
			credits[28].set("",RGB(255,0,0));
			credits[29].set("",RGB(255,0,0));
			credits[30].set("",RGB(255,0,0));
			credits[32].set("",RGB(255,0,0));
			credits[33].set("",RGB(255,0,0));
			
		}
		
		virtual void update()
		{
			draw();
			logic();
		}
		
	private:
		
		
		int credit_off;
		int i;
		
		
		inline void draw()
		{
			for(i = 0; i < 200; i++)
			{
				if(credits[i].on == true)
				{
					mxhwnd.text.settextcolor(credits[i].color);
					mxhwnd.text.printtext(credits[i].str,credits[i].x,credits[i].y);
				}
			}
		}
		
		inline void logic()
		{
			
			for(i = 0; i < 200; i++)
			{
				if(credits[i].on == true)
				{
					credits[i].y--;
					if(credits[i].y == 170)
					{
						credits[i].reset();
					}
				}
			}
			
			static int t_count = 0;
			if(++t_count > 15)
			{
				t_count = 0;
				credits[credit_off].on = true;
				credit_off++;
				if(credit_off > 33)
				{
					credit_off = 0;
				}
				
			}
			
		}
		
		struct Credit
		{
			char str[100];
			int x;
			int y;
			bool on;
			Uint32 color;
			
			
			inline void set(char* xstr,Uint32 colorx)
			{
				strcpy(str,xstr);
				color = colorx;
				x = 100;
				y = 460;
			}
			
			inline void reset()
			{
				x = 100;
				y = 460;
				on = false;
			}
		};
		
		Credit credits[200];
		
};

Credits credits;

};

const int MAX_TILE = 8000;

// game Level structure
struct Level
{
	struct Tile
	{
		int block;
		bool solid;
	};
	
	
	
	char level_name[255];
	int grandma[50]; 
	int start_pos;
	Tile tiles[MAX_TILE];
	
	inline Level()
	{
		strcpy(level_name,"null");
		for(int i = 0; i < MAX_TILE; i++)
		{
			tiles[i].block = 1;
			tiles[i].solid = false;
		}
	}
};

Level level;

const int MAX_PARTICLE = 500;


class ParticleEmiter : public MasterGameObject
{
public:
	virtual void load()
	{
		shot.SetColorKey(RGB(255,255,255));
		mxhwnd.LoadGraphic(&shot,"shot.bmp");

	}

	virtual void update()
	{
		draw();
		Sync
		{
			logic();
		}
	}


	inline void releaseparticle(int x ,int type, bool dir)
	{
		int off;
		off = getoffparticle();
		if(off != -1)
		{
			particles[off].pos = x;
			particles[off].type = type;
			particles[off].dir = dir;
		}
	}


	int mx,my;
	MasterGraphic shot;
	
	inline void draw()
	{
		for(i = 0; i < MAX_PARTICLE; i++)
		{
			switch(particles[i].type)
			{
			case 1:
				{
					GetPointFromPos(particles[i].pos,mx,my);
					if(mx == 0 && my == 0)
					{
						particles[i].type = -1;
						break;
					}
					shot.DisplayGraphic(mx,my);
				}
				break;
			case 2:
				{
					GetPointFromPos(particles[i].pos,mx,my);
					if(mx != 0 && my != 0)
					{

					//mxhwnd.paint.mxdrawellipse(mx,my,mx+16,my+16,RGB(rand()%255,rand()%255,rand()%255),RGB(rand()%255,rand()%255,rand()%255));
						shot.DisplayGraphic(mx,my);


					}
					else
					{
						particles[i].type = -1;
					} 

				}
				break;
			}
		}
		
	}

	inline void logic()
	{
		for(i = 0; i < MAX_PARTICLE; i++)
		{
			switch(particles[i].type)
			{
			case 1:
				{
					if(particles[i].dir == true)
					{

					particles[i].pos += 24;

					}
					else
					{
						particles[i].pos -= 24;
					}

					if(level.tiles[particles[i].pos + getoff_set()].solid == true)
					{
						particles[i].pos = 0;
						particles[i].type = -1;
					}
				}
				break;
			case 2:
				{
					if(particles[i].dir == true)
					{
						particles[i].pos += 24;
					}
					else
					{
						particles[i].pos -= 24;
					}

					if(level.tiles[particles[i].pos].solid == true || level.tiles[particles[i].pos+1].solid == true || level.tiles[particles[i].pos-1].solid == true || level.tiles[particles[i].pos+getoff_set()].solid == true )
					{
						particles[i].pos = 0;
						particles[i].type = -1;
					}

					GetPointFromPos(particles[i].pos,mx,my);
					if(mx == 0 || my == 0)
					{
						particles[i].pos = 0;
						particles[i].type = -1;
					}

					

				}
				break;
			}
		}
	}


	int i;

	struct Particle
	{
		int pos;
		int type;
		bool dir;

		inline Particle()
		{
			type = -1;
			pos = 0;
			dir = false;
		}
	};

	Particle particles[MAX_PARTICLE];

	inline int getoffparticle()
	{
		for(i = 0; i < MAX_PARTICLE; i++)
		{
			if(particles[i].type == -1)
			{
				return i;
			}
		}

		return -1; // fail
	}

};



class Hero : public MasterGameObject
{
public:
	
	int pos;
	bool dir;
	
	
	virtual void load()
	{
		for(int p = 0; p < 10; p++)
		{
			left[p].SetColorKey(RGB(255,255,255));
			right[p].SetColorKey(RGB(255,255,255));
		}

		mxhwnd.LoadGraphic(&left[0],"Hero1.bmp");
		mxhwnd.LoadGraphic(&left[1],"Hero2.bmp");
		mxhwnd.LoadGraphic(&left[2],"Hero3.bmp");
		mxhwnd.LoadGraphic(&left[3],"Hero4.bmp");
		mxhwnd.LoadGraphic(&left[4],"Hero_jump1.bmp");
		mxhwnd.LoadGraphic(&left[5],"Hero_shot1.bmp");
		mxhwnd.LoadGraphic(&left[6],"Hero_shot2.bmp");
		mxhwnd.LoadGraphic(&left[7],"Hero_shot3.bmp");
		mxhwnd.LoadGraphic(&left[8],"Hero_shot4.bmp");
		mxhwnd.LoadGraphic(&left[9],"Hero_shot5.bmp");
		
		mxhwnd.LoadGraphic(&right[0],"Hero1_l.bmp");
		mxhwnd.LoadGraphic(&right[1],"Hero2_l.bmp");
		mxhwnd.LoadGraphic(&right[2],"Hero3_l.bmp");
		mxhwnd.LoadGraphic(&right[3],"Hero4_l.bmp");
		mxhwnd.LoadGraphic(&right[4],"Hero_jump1_l.bmp");
		mxhwnd.LoadGraphic(&right[5],"Hero_shot1_l.bmp");
		mxhwnd.LoadGraphic(&right[6],"Hero_shot2_l.bmp");
		mxhwnd.LoadGraphic(&right[7],"Hero_shot3_l.bmp");
		mxhwnd.LoadGraphic(&right[8],"Hero_shot4_l.bmp");
		mxhwnd.LoadGraphic(&right[9],"Hero_shot5_l.bmp");

		mxhwnd.LoadSound(&sfire,"fire.wav");
		
		dir = true;
		curimg = 0;
		jump = false;
		jumpok = true; 
		air = false;
		
		
		
		
		
	}
	
	virtual void update()
	{
		draw();
		logic();
	}
	
	inline void keyup(int key)
	{
		switch(key)
		{
		case VK_LEFT:
		case VK_RIGHT:
			curimg = 0;
			break;
		}
	}
	
	
private:
	MasterGraphic left[10];
	MasterGraphic right[10];
	MasterSound   sfire;
	int px,py;
	int curimg;
	bool jump,jumpok;
	bool check1,check2,check3,check4,check5;
	int jumpi;
	bool fall;
	bool fire;
	bool air;

	
	
	inline void draw()
	{
		GetPointFromPos(pos,px,py);
		if(dir == true)
		{
			left[curimg].DisplayGraphic(px,py);
		}
		else
		{
			right[curimg].DisplayGraphic(px,py);
		}
	}
	
	inline void logic()
	{
		

		if(fire == false)
		{

		if(mxhwnd.KeyCheck(DIK_LEFT))
		{
			heroleft();
		}
		
		if(mxhwnd.KeyCheck(DIK_RIGHT) )
		{
			heroright();
			
		}
		
		if(mxhwnd.KeyCheck(DIK_A))
		{
			if(air == false)
			{

			herojump();

			}
		}
		
		if(mxhwnd.KeyCheck(DIK_S))
		{
			if(jumpok == true && fall == false && jumpok == true && air == false)
			{

			sfire.Play();
			herofire();

			}
		}

		procjump();
		procblock();
		
	
		}
		else
		{
			
			fireproc();
		}
		
	
	}
	
	inline void heroleft()
	{
		dir = false;
		
		if(getoff_set() == 0)
		{
			if(pos > 0)
			{
				
			
			check1 = level.tiles[pos-24].solid;
			check2 = level.tiles[pos+1-24].solid;
			check3 = level.tiles[pos+2-24].solid;
			check4 = level.tiles[pos+3-24].solid;
			check5 = level.tiles[pos-24-24].solid;
	
				
				if(check1 == false && check2 == false && check3 == false && check4 == false && check5 == false)
				{
					
					pos -= 24;
					
					if(jump == false && fall == false && air == false)
					{
						
						curimg++;
						if(curimg > 3)
						{
							curimg = 0;
						}
						
					}
					else
					{
						curimg = 4;
					}
				}
				else
				{
					curimg = 0;
				}
			}
		}
		else
		{
		
			check1 = level.tiles[pos+getoff_set()-24].solid;
			check2 = level.tiles[pos+getoff_set()+1-24].solid;
			check3 = level.tiles[pos+getoff_set()+2-24].solid;
			check4 = level.tiles[pos+getoff_set()+3-24].solid;
			check5 = level.tiles[pos+getoff_set()-24-24].solid;


					
			if(check1 == false && check2 == false && check3 == false && check4 == false && check5 == false)
			{
				scrollleft();
				
				if(jump == false && fall == false && air == false)
				{
					
					curimg++;
					if(curimg > 3)
					{
						curimg = 0;
					}
					
				}
				else
				{
					curimg = 4;
				}
			}
			else
			{
				curimg = 0;
			}
		}
	}
	
	inline void heroright()
	{
		dir = true;
		
		if(pos < 24*15)
		{
			
			
			check1 = level.tiles[pos + 27].solid;
			check2 = level.tiles[pos + 27 + 24].solid;
			check3 = level.tiles[pos + 27 + 23].solid;
			check4 = level.tiles[pos + 27 + 22].solid;
			check5 = level.tiles[pos + 27 + 21].solid;
			
			if(check1 == false && check2 == false && check3 == false && check4 == false && check5 == false)
			{
				
				
				pos += 24;
				
				if(jump == false && fall == false && air == false)
				{
					
					
					curimg++;
					if(curimg > 3)
					{
						curimg = 0;
					}
					
				}
				else
				{
					curimg = 4;
				}
				
			}
			else
			{
				curimg = 0;
			}
			
		}
		else
		{
			check1 = level.tiles[pos + 27+getoff_set()].solid;
			check2 = level.tiles[pos + 27 + 24+getoff_set()].solid;
			check3 = level.tiles[pos + 27 + 23+getoff_set()].solid;
			check4 = level.tiles[pos + 27 + 22+getoff_set()].solid;
			check5 = level.tiles[pos + 27 + 21+getoff_set()].solid;
			if(check1 == false && check2 == false && check3 == false && check4 == false && check5 == false)
			{
				scrollright();
				
				if(jump == false && fall == false && air == false)
				{
					
					curimg++;
					if(curimg > 3)
					{
						curimg = 0;
					}
					
				}
				else
				{
					curimg = 4;
				}
			}
			else
			{
				curimg = 0;
			}
		}
	}
	
	inline void herojump()
	{
		if(jumpok == true)
		{
			jump = true;
			jumpi = 0;
			jumpok = false;
			
		}
	}
	
	inline void procjump()
	{
		if(jump == true)
		{
			check1 = level.tiles[pos-1+getoff_set()].solid;
			check2 = level.tiles[pos+24-1+getoff_set()].solid;
			if(check1 == false && check2 == false)
			{
				fall = true;
				pos--;
				jumpi++;
				if(jumpi > 8)
				{
					jumpi = 0;
					jump = false;
					
				}
				
			}
			else
			{
				jumpi = 0;
				jump = false; 
				fall = false;
			}
		}
		
	}
	
	
	inline void procblock()
	{
		static int t_count = 0;
		
		if(++t_count > 1)
		{
			
			check1 = level.tiles[pos+getoff_set()+4].solid;
			check2 = level.tiles[pos+getoff_set()+24+4].solid;
			if(check1 == false && check2 == false)
			{
				pos++;
				curimg = 4;
				air = true;
			}
			else
			{
				// we have landed
				jumpok = true;
				jump  = false;
				curimg = 0;
				fall = false;
				air = false;
			}
			
			t_count = 0;
		}
	}

	inline void herofire()
	{ 

		if(jumpok == true && fall == false)
		{

		fire = true;
		curimg = 0;

		}

	}

	inline void fireproc()
	{
		int temp = getnextfire();
		if(temp == -1)
		{
			fire = false;
			curimg = 0;
			releaseparticle(pos+2,1,dir);
		}
		else
		{
			curimg = temp;
		}
	}


	int getnextfire()
	{
		switch(curimg)
		{
		case 0:
			return 5;
			break;
		case 5:
			return 6;
			break;
		case 6:
			return 7;
			break;
		case 7:
			return 8;
			break;
		case 8:
			return 9;
			break;
		case 9:
			return -1;
			break;
		}

		return 0;
	}

	
};

class Grandma : public MasterGameObject
{
public:

int pos;
bool dead;
bool gone;

	virtual void load()
	{
		for(i = 0; i < 10; i++)
		{
			gleft[i].SetColorKey(RGB(255,255,255));
			gright[i].SetColorKey(RGB(255,255,255));
		}

		mxhwnd.LoadGraphic(&gleft[0],"grandma_1.bmp");
		mxhwnd.LoadGraphic(&gleft[1],"grandma_2.bmp");
		mxhwnd.LoadGraphic(&gleft[2],"grandma_3.bmp");
		mxhwnd.LoadGraphic(&gleft[3],"grandma_4.bmp");
		mxhwnd.LoadGraphic(&gleft[4],"grandma_5.bmp");
		mxhwnd.LoadGraphic(&gleft[5],"grandma_die1.bmp");
		mxhwnd.LoadGraphic(&gleft[6],"grandma_die2.bmp");
		mxhwnd.LoadGraphic(&gleft[7],"grandma_die3.bmp");
		mxhwnd.LoadGraphic(&gleft[8],"grandma_die4.bmp");
		mxhwnd.LoadGraphic(&gleft[9],"grandma_die5.bmp");

		mxhwnd.LoadGraphic(&gright[0],"grandma_1_l.bmp");
		mxhwnd.LoadGraphic(&gright[1],"grandma_2_l.bmp");
		mxhwnd.LoadGraphic(&gright[2],"grandma_3_l.bmp");
		mxhwnd.LoadGraphic(&gright[3],"grandma_4_l.bmp");
		mxhwnd.LoadGraphic(&gright[4],"grandma_5_l.bmp");
		mxhwnd.LoadGraphic(&gright[5],"grandma_die1_l.bmp");
		mxhwnd.LoadGraphic(&gright[6],"grandma_die2_l.bmp");
		mxhwnd.LoadGraphic(&gright[7],"grandma_die3_l.bmp");
		mxhwnd.LoadGraphic(&gright[8],"grandma_die4_l.bmp");
		mxhwnd.LoadGraphic(&gright[9],"grandma_die5_L.bmp");

		dir = true;
		dead = false;

		

		tdir = false;
		
	}

	virtual void update()
	{
		if(gone == false)
		{

		draw();
		logic();
		
		}
	}

	void releasegrandma()
	{


	}

	void Die()
	{
		dead = true;
		curimg = 4;

	}




private:

	MasterGraphic gleft[15];
	MasterGraphic gright[15];
	int i; 
	bool dir;
	int mx,my;
	int curimg;
	bool check1,check2,check3,check4,check5;
	bool tdir;
	bool air;




	inline void draw()
	{
	
		GetPointFromPos(pos-getoff_set(),mx,my);

		if(mx != 0 && my != 0)
		{


		if(dir == true)
		{
			gleft[curimg].DisplayGraphic(mx,my);
		}
		else
		{
			gright[curimg].DisplayGraphic(mx,my);
		}

		}
	}

	inline void logic()
	{
		if(dead == false)
		{


		procblocks();
		ai();
	
		}
		else
		{

		DieProc();

		}

	}

	inline void ai()
	{
		if(tdir == true)
		{
			moveright();
		}
		else
		{
			moveleft();
		}

		

	
	}
	
	void moveleft()
	{
		if(air == false)
		{

			
			static int r_count = 0;
			if(++r_count > 1)
			{
				dir = false;
				check1 = level.tiles[pos-24].solid;
				check2 = level.tiles[pos+1-24].solid;
				check3 = level.tiles[pos+2-24].solid;
				check4 = level.tiles[pos+3-24].solid;
				check5 = level.tiles[pos-24-24].solid;
				
				static int x_count = 0;
				if(++x_count > 8)
				{
					releaseparticle(pos+2-getoff_set(),2,dir);
					x_count = 0;
				}

				
				if(check1 == false && check2 == false && check3 == false && check4 == false && check5 == false)
				{
					curimg ++;
					if(curimg > 4 )
					{
						curimg = 0;
					}
					pos -= 24;
					
				}
				else
				{
					tdir = true;
					dir = true;
				}
				
				r_count = 0;
			}
		}
	}
	
	void moveright()
	{
		if(air == false)
		{
			static int z_count = 0;
			
			if(++z_count > 1)
			{
				dir = true;

				static int x_count = 0;
				if(++x_count > 8)
				{
					releaseparticle(pos+2-getoff_set(),2,dir);
					x_count = 0;
				}
				
				check1 = level.tiles[pos + 27].solid;
				check2 = level.tiles[pos + 27 + 24].solid;
				check3 = level.tiles[pos + 27 + 23].solid;
				check4 = level.tiles[pos + 27 + 22].solid;
				check5 = level.tiles[pos + 27 + 21].solid;
				
				if(check1 == false && check2 == false && check3 == false && check4 == false && check5 == false)
				{
					pos += 24;
					curimg ++;
					if(curimg > 4)
					{
						curimg = 0;
					}
					
					z_count = 0;
				}
				else
				{
					tdir = false;
					dir = false;
				}
			}
		}
		
	}

	void procblocks()
	{
	 
			
			check1 = level.tiles[pos+4].solid;
			check2 = level.tiles[pos+24+4].solid;
			if(check1 == false && check2 == false)
			{
				pos++;
				curimg = 0;
				air = true;
			}
			else
			{
				air = false;
			}
			
		
	}


	void DieProc()
	{
		if(dead == true)
		{
			static int i_count = 0;
			if(++i_count > 1)
			{
				curimg++;
				if(curimg > 9)
				{
					gone = true;
				}
				i_count = 0;
			}
		}
	}

};


class Game : public MasterGameObject
{
public:
	virtual void load()
	{
		// first load up the tiles
		mxhwnd.LoadGraphic(&tiles[0],"black.bmp");
		mxhwnd.LoadGraphic(&tiles[1],"grass.bmp");
		mxhwnd.LoadGraphic(&tiles[2],"bluebrick.bmp");
		mxhwnd.LoadGraphic(&tiles[3],"bluesky.bmp");
		mxhwnd.LoadGraphic(&tiles[4],"brick.bmp");
		mxhwnd.LoadGraphic(&tiles[5],"eblock.bmp");
		mxhwnd.LoadGraphic(&tiles[6],"red_brick.bmp");
		mxhwnd.LoadGraphic(&tiles[7],"sand1.bmp");
		mxhwnd.LoadGraphic(&tiles[8],"sand2.bmp");
		mxhwnd.LoadGraphic(&tiles[9],"snow.bmp");
		mxhwnd.LoadGraphic(&tiles[10],"stone.bmp");
		mxhwnd.LoadGraphic(&tiles[11],"stone2.bmp");
		mxhwnd.LoadGraphic(&tiles[12],"stone3.bmp");
		mxhwnd.LoadGraphic(&tiles[13],"stone4.bmp");
		mxhwnd.LoadGraphic(&tiles[14],"black.bmp"); //level exit block
		mxhwnd.LoadGraphic(&bg,"gamebg.bmp");//game background
		hero.load();
		emiter.load();
	
		// will be a loop soon
		for(i = 0; i < 50; i++)
		{
			grandma[i].load();
		}
		gameinit();
	}
	
	virtual void update()
	{
		draw();
		Sync
		{
			logic();
		}
		
		hero.update();
		emiter.update();

		// soon to be a loop
		for(i = 0; i < 50; i++)
		{
			if(level.grandma[i] != 0)
			{

			grandma[i].update();

			}
		}

		if(level.tiles[hero.pos+off_set].block == 14)
		{
			cur_level++;
			mxhwnd.SetScreen(ID_LAUNCH);
		}
	}
	
	inline void gameover()
	{
		
	}
	
	inline void gameinit()
	{
		resetgame();
		
	}
	
	inline void loadlevel(char* filename)
	{
		ifstream fin(filename,ios::binary);
		fin.read((char*)&level,sizeof(level));
		fin.close();
		for(i = 0; i < 50; i++)
		{
			if(level.grandma[i] != 0)
			{
				grandma[i].pos = level.grandma[i];
				grandma[i].dead = false;
				grandma[i].gone = false;
			}
		}
		hero.pos = level.start_pos;
		off_set = 0;
	}
	
	inline int getoffset()
	{
		return off_set;
	}
	
	inline void keyup(int key)
	{
		hero.keyup(key);
	}
	
	inline void moveleft()
	{
		if(off_set > 0)
		{
			off_set -= 24;
		}
	}
	
	inline void moveright()
	{
		if(off_set < MAX_TILE)
			
		{
			off_set += 24;
		}
	}
	
	
	inline void resetgame()
	{
		lives = 15;
		score = 0;
		kills = 0;
		off_set = 0;
		cur_level = 1;
	}

	Hero hero;
	ParticleEmiter emiter;
	Grandma grandma[50];


	
private:
	MasterGraphic tiles[15];
	MasterGraphic bg;
	int off_set;
	int i; // loop variable
	int mx,my;
	int z;
	
	
	inline void draw()
	{
		//bg.DisplayGraphic(0,0);
		mxhwnd.text.settextcolor(RGB(0,0,255));
		mxhwnd.paint.mxdrawrect(0,0,640,30,0x0,0x0);
		mxhwnd.text.sprinttext(10,10," SuperMaster - %s - Score (%d) - Lives (%d) - Kills (%d)",level.level_name,score,lives,kills);
		drawmap();
	}

	int gx,gy;
	
	inline void logic()
	{
		// cycle through the emiter's current particles
		// with the hero's x/y
		for(i = 0; i < MAX_PARTICLE; i++)
		{
			switch(emiter.particles[i].type)
			{
			case 1:
				{
					GetPointFromPos(emiter.particles[i].pos,mx,my);
					for(z = 0; z < 50; z++)
					{
						if(grandma[z].gone == false)
						{

						GetPointFromPos(grandma[z].pos-getoff_set(),gx,gy);
						if(mx >= gx && mx <= gx+32 && my >= gy && my <= gy+64)
						{
							emiter.particles[i].type = -1;
							grandma[z].Die();
							kills++;
							score += 5;
						}

						}
					}
				}
				break;
			case 2:
				{
					GetPointFromPos(hero.pos,gx,gy);
					GetPointFromPos(emiter.particles[i].pos,mx,my);

					if(mx >= gx && mx <= gx+32 && my >= gy && my <= gy+64)
					{
						lives--;
						for(i = 0; i < MAX_PARTICLE; i++)
						{
							emiter.particles[i].type = -1;
						}
						if(lives == -1)
						{
							resetgame();
							mxhwnd.SetScreen(ID_GAMEOVER);
						}

						hero.pos = level.start_pos;
						off_set = 0;
					}

				}
				break;
			}
		}
		
	}

	
	inline void drawmap()
	{
		static int startby;
		startby = 75;
		static int bx,by;
		bx = 50; by = startby;
		int gcount = 0;
		
		
		for(i = 0; i < 700-4+24; i++)
		{
			
			tiles[level.tiles[off_set+i].block].DisplayGraphic(bx,by);
			
			by = by + 16;
			gcount++;
			if(gcount > 23)
			{
				gcount = 0;
				by = startby;
				bx = bx + 16;
			}
			
		}
	}
	
	
};

struct LevelName
{
	char data[255];
	void operator=(char* datax)
	{
		strcpy(data,datax);
	}
};


class Launch :  public MasterGameObject
{
public:

	LevelName levels[8];

	virtual void load()
	{
		xhero.SetColorKey(RGB(255,255,255));
		ehero.SetColorKey(RGB(255,255,255));
		
		mxhwnd.LoadGraphic(&bg,"start.bmp");
		mxhwnd.LoadGraphic(&xhero,"grandma_1.bmp");
		mxhwnd.LoadGraphic(&ehero,"xhero.bmp");
		levels[0] = "level1.sml";
		levels[1] = "level2.sml";
		levels[2] = "level3.sml";
		levels[3] = "level4.sml";
		levels[4] = "level5.sml";
		levels[5] = "level6.sml";
		levels[6] = "level7.sml";
		levels[7] = "level8.sml";
		
	}

	virtual void update()
	{
		draw();
		Sync
		{
			logic();
		}
	}

	inline void keypress(int key)
	{
		if(key == VK_RETURN)
		{

			if(cur_level == 9)
			{
				setcredits();
			}
			else
			{

		// load the level
		load_level(levels[cur_level-1].data);
		mxhwnd.SetScreen(ID_GAME);

			}


		}	
	}

private:

 
	inline void draw()
	{
		bg.DisplayGraphic(0,0);
		xhero.DisplayGraphic(100,100);
		mxhwnd.paint.mxdrawrect(10,100,470,270,0x0,0x0);
		mxhwnd.text.settextcolor(RGB(200,0,0));
		mxhwnd.text.sprinttext(20,120," Now Entering Level (%d) \n- press enter key to continue",cur_level);
		ehero.DisplayGraphic(25,180);
		mxhwnd.text.sprinttext(200+36+5,150," Lives: %i",lives);

		if(cur_level == 9)
		{
			setcredits();
		}


	}

	inline void logic()
	{

	}


	MasterGraphic bg;
	MasterGraphic xhero;
	MasterGraphic ehero;


};

 
class GameOver : public MasterGameObject
{
public:
	
	virtual void load()
	{
		mxhwnd.LoadGraphic(&bg,"gameover.bmp");
	}
	
	virtual void update()
	{
		bg.DisplayGraphic(0,0);
	}

	inline void keypress(int key)
	{
		if(key == VK_RETURN)
		{

		mxhwnd.SetScreen(ID_START);

		}

	}

	MasterGraphic bg;
	
};