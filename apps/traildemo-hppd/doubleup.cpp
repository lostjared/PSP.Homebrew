

#include"mx.h"

#include<stdlib.h>
#include<time.h>
void mix_in_image();
void shift_up();
void shift_down();
void update_screen(int scr);
void onEvent(SDL_Event *evnt);
void keyfunc(int key);
void keyfuncup(int key);
void mousemove(int x, int y);
void mousedown(int button, int x, int y);
void release_explosion();
void change_image();
void update_cords();
bool its_running = false;
int tx_pos, ty_pos,image_index = 0;
int amount = 240*125;
void init_joy();

#define screen_width 240*125+1

ArrayOf array_of_pixels[screen_width];
mxHwnd mxhwnd;
mxSprite logo;
SDL_Joystick *joy_stick[6];
int stick_axis[3];

extern "C" int SDL_main(int argc, char *argv[]);

int SDL_main(int argc, char *argv[])
{
    tx_pos = 0;
    ty_pos = 0;

    srand(time(0));
	if(mxhwnd.init("HPPD in SDL w/ Joystick Support",240,125,0,false) == 0)
	{     
     logo.load(&mxhwnd, "blackdots.bmp");  
	    init_joy();
	    for(int z = 0; z <= rand()%4; z++)
	    {
	        change_image();
	   }        
	   
	   	mxhwnd.setScreen(0);
		mxhwnd.setEventHandler(onEvent);
		mxhwnd.setKeydown(keyfunc);
		mxhwnd.setKeyup(keyfuncup);
//		mxhwnd.setMouseDown(mousedown);
//		mxhwnd.setMouseMove(mousemove);
		mxhwnd.initLoop(update_screen);
		for(int i = 0; i < SDL_NumJoysticks(); i++)
		SDL_JoystickClose(joy_stick[i]);
	}
	return 0;

}

void init_joy()
{
    if(SDL_NumJoysticks() == 0)
    {
        printf("Joystick not found...\n");
       return;
   }              
   else 
   {
 
 for(int i = 0; i < SDL_NumJoysticks(); i++)
       joy_stick[i] = SDL_JoystickOpen(i);      
                      

SDL_JoystickEventState(SDL_ENABLE);

}

}

void update_screen(int scr)
{


    logo.display(0,0);

	mxhwnd.buf = lock(mxhwnd.pscr, mxhwnd.pscr->format->BitsPerPixel);

    static bool init_a = false;

    if(init_a == false)
    {
        for(int i = 0; i < 240*125; i++)
        {
            array_of_pixels[i].init(&mxhwnd);
            array_of_pixels[i].color_r = rand()%255;
            array_of_pixels[i].color_g = rand()%255;
            array_of_pixels[i].color_b = rand()%255;
            array_of_pixels[i].setDirection(rand()%240,rand()%125,rand()%4);                
        }
        
        init_a = true;

        }
	
        if(its_running == true)
        {
            

	static int rr = 0, rg = 0, rb = 0;
	if(rr == 0) {
		rr = rand()%255;
		rg = rand()%255;
		rb = rand()%255;
	}

    
  
        for(int i = 0; i < amount; i++)
        {

            if(array_of_pixels[i].x_pos >= tx_pos && array_of_pixels[i].x_pos <= tx_pos+25 && array_of_pixels[i].y_pos >= ty_pos && array_of_pixels[i].y_pos <= ty_pos+25)
            {
                array_of_pixels[i].color_r = rr;
                array_of_pixels[i].color_g = rg;
                array_of_pixels[i].color_b = rb;
                array_of_pixels[i].setDirection(tx_pos,ty_pos,rand()%5);
        }        
      
           array_of_pixels[i].render();
       }    

       rr = rand()%255, rg = rand()%255, rb = rand()%255;       
       }        


	unlock(mxhwnd.pscr);       

       update_cords();
    
        SDL_UpdateRect(mxhwnd.pscr,0,0,240,125);

                    
}

void update_cords()
{     
    if(stick_axis[0] > 100)
	if(tx_pos < 240-15)
        tx_pos+=15;
    if(stick_axis[0] < -100)
	if(tx_pos > 0)
        tx_pos-=15;       
    if(stick_axis[1] > 100)
	if(ty_pos < 125)
        ty_pos+=15;
   if(stick_axis[1] < -100)
	if(ty_pos > 0)
        ty_pos-=15;
        
        for(int z = 0; z < SDL_NumJoysticks(); z++)
        {
            
        if(SDL_JoystickGetButton(joy_stick[z],5))
        {
            change_image();
    }    
    
    if(SDL_JoystickGetButton(joy_stick[z],0))
    {
        shift_up();
    }        
    
    if(SDL_JoystickGetButton(joy_stick[z],1))
    {
        shift_down();
    }
    if(SDL_JoystickGetButton(joy_stick[z],2))
    {
        release_explosion();
        return;
    }
    if(SDL_JoystickGetButton(joy_stick[z],3))
    {
        mix_in_image();
    }            
    if(SDL_JoystickGetButton(joy_stick[z],9))
     {
         its_running = true;
    }          
}                
        
   SDL_UpdateRect(mxhwnd.pscr,0,0,240,125);        
}

void onEvent(SDL_Event *evnt)
{
    
    switch(evnt->type)
    {
        case SDL_JOYAXISMOTION:
            if(evnt->jaxis.axis < 2)
            stick_axis[evnt->jaxis.axis]=evnt->jaxis.value>>8;   
            update_cords(); 
            break;
    }    
}

void mix_in_image()
{
    int pos = 0;
    for(int i = 0; i < 240; i++)
    {
        for(int z = 0; z < 125; z++)
           {
                  Uint32 color = mxhwnd.getPixel(mxhwnd.pscr,i,z);
                  array_of_pixels[pos].setDirection(i,z,rand()%6);
                  array_of_pixels[pos].setColor(color);     
                  pos++;
           }    
 }                           
}

void keyfunc(int key)
{

printf("%d", key);


switch(key)
{
case 13:

    release_explosion();
    printf("Released..\n");   

break;
case 273:
    shift_up();
    break;
    case 274:
        shift_down();
        break;
        case 32:
            mix_in_image();
            break;
            case 27:
                mxhwnd.kill();
                break;
                case 275:
                    case 276:
                       change_image();
                        break;
                        case 'a':
                            case 'A':
                                if(amount > 0)
                                amount -= 100;
                                break;
                                case 'S':
                                    case 's':
                                        if(amount < 240*125)
                                        {
                                     amount += 10;       
                                    }    
                                        break;
                        
}

}
void keyfuncup(int key)
{

}
void mousemove(int x, int y)
{
    tx_pos = x;
    ty_pos = y;
    
}
void mousedown(int button, int x, int y)
{
switch(button)
   {
       case 1:
            for(int i = 0; i < 240*125;i++)
            {
                       array_of_pixels[i].setDirection(array_of_pixels[i].x_pos, array_of_pixels[i].y_pos, rand()%6);      
            } 
            break;
            case 2:
                            for(int i = 0; i < 240*125;i++)
            {
                       array_of_pixels[i].setDirection(array_of_pixels[i].x_pos, array_of_pixels[i].y_pos, rand()%2 >= 1 ? 5 : 6 );      
            } 
            break;
                                        
  } 
                 
}

void release_explosion()
{ 
  its_running = true;                     
}    

void shift_up()
{
 for(int i = 0; i < 240*125; i++)
 {
     if(array_of_pixels[i].x_pos >= 0 && array_of_pixels[i].x_pos <= 240 && array_of_pixels[i].y_pos >= 440 && array_of_pixels[i].y_pos <= 125)
     {
         array_of_pixels[i].setDirection(array_of_pixels[i].x_pos,array_of_pixels[i].y_pos,rand()%6);           
}     
}  
}   

void shift_down()
{
 
    for(int i = 0; i < 240*125; i++)
 {
     if(array_of_pixels[i].x_pos >= 0 && array_of_pixels[i].x_pos <= 240 && array_of_pixels[i].y_pos >= 0 && array_of_pixels[i].y_pos <= 40)
     {
         array_of_pixels[i].setDirection(array_of_pixels[i].x_pos,array_of_pixels[i].y_pos,rand()%6);           
}     
}   
    
}

void change_image()
{
    image_index++;
    if(image_index >= 6)
    image_index = 0;
    switch(image_index)
    {
        case 1:
            logo.~mxSprite();
            logo.load("logo2.bmp");
            logo.display(0,0);
            SDL_UpdateRect(mxhwnd.pscr,0,0,240,125);
            
            break;
            case 2:
                logo.~mxSprite();
            logo.load("logo3.bmp");
            logo.display(0,0);
            SDL_UpdateRect(mxhwnd.pscr,0,0,240,125);
            
                break;
                case 3:
                    logo.~mxSprite();
            logo.load("logo4.bmp");
            logo.display(0,0);
            SDL_UpdateRect(mxhwnd.pscr,0,0,240,125);
            
                    break;
                    case 4:
                        logo.~mxSprite();
            logo.load("blackdots.bmp");
            logo.display(0,0);
            SDL_UpdateRect(mxhwnd.pscr,0,0,240,125);
            break;
            case 5:
                 logo.~mxSprite();
                 logo.load("logo1.bmp");
                 logo.display(0,0);
                 SDL_UpdateRect(mxhwnd.pscr,0,0,240,125);
                 break;
                    }               
}
