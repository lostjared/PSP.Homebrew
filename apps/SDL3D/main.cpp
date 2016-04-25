#include<SDL.h>
#include "mx3d_math.h"

SDL_Surface *front = 0;
SDL_Joystick *stick = 0;
void *buf = 0;


const int uni_rad = 4000, point_size = 200, num_points_x = 2*uni_rad/point_size, num_points_y = 2*uni_rad/point_size, num_points_z = num_points_y*num_points_z;
const int num_towers = 96, num_tanks = 24, tank_speed = 25;

mx3d::vec4D cam_pos(0,40,40,1), cam_target(0,0,0,1), cam_dir(0,0,0,1), vscale(1.0f,1.0f,1.0f,1.0f),vrot(0,0,0,1),vpos(0,0,0,1);
mx3d::Camera cam;
mx3d::mxObject tower,tank,player,marker;
mx3d::vec4D tower_points[num_towers], tank_points[num_tanks];
mx3d::RenderList rl;
mx3d::PipeLine graph;
mx3d::Mat4D mrot;
float turning = 0;
int axis[2] = { 0 , 0 };

void proc_axis() ;


inline bool CullObject(mx3d::mxObject &o, mx3d::Camera &cam) {
	return (o.CullObject(true,true,true,cam.mcam,cam.far_clip_z,cam.near_clip_z,cam.viewplane_width, cam.viewplane_height, cam.view_dist));
}

void render(int screen) {
	//mxhwnd.paint.drawrect(0,0,mxhwnd.w-1,mxhwnd.h-1,D3DCOLOR_XRGB(0,0,255));
	//mxhwnd.paint.drawrect(0,mxhwnd.h/2, mxhwnd.w-1, mxhwnd.h-1, D3DCOLOR_XRGB(0,0,200));
	//mxhwnd.SetTicks();

	static float view_angle = 0.0f, camera_dist = 6000.0f,tank_speed = 0.0f;
	mx3d::vec4D pos(0,0,0,0);

	rl.Reset();
	tank_speed = 25;



	cam.BuildEuler(5);
	int i;



	for(i = 0; i < num_tanks; i++) {
		tank.Reset();
		mrot.BuildXYZ(0,tank_points[i].w, 0);
		tank.TransformObject(mrot,1);
		tank.world_pos.x = tank_points[i].x;
		tank.world_pos.y = tank_points[i].y;
		tank.world_pos.z = tank_points[i].z;
		if(!CullObject(tank,cam)) {
			tank.ModelToWorld();
			tank.BuildRenderList(rl);
		}
	}

	mrot.BuildXYZ(0,cam.dir.y+turning,0);
	
	for(i = 0;  i < num_towers; i++) {
		tower.Reset();
		tower.world_pos.x = tower_points[i].x;
		tower.world_pos.y = tower_points[i].y;
		tower.world_pos.z = tower_points[i].z;
		if(!CullObject(tower,cam)) {
			tower.ModelToWorld();
			tower.BuildRenderList(rl);
		}
	}

	rl.RemoveFaces(cam.pos);
	cam.WorldToCamera(rl);
	cam.CameraToPerspective(rl);
	cam.PerspectiveToScreen(rl);
	graph.Begin();
	graph.DrawSolidPolys(rl);
	graph.End();


	proc_axis();
}


int Init() {
	mx3d::BuildTables();
	// init code here
	cam.Init(0,cam_pos,cam_dir,0,200.0f,12000.0f,120.0f,float(front->w),float(front->h));
	vscale.Set(0.75f,0.75f,0.75f,1.0f);
	if(!tank.LoadPLG("tank2.plg", vscale, vpos, vrot, D3DCOLOR_XRGB(200,200,200))) 
		return 1;
	vscale.Set(0.75,0.75,0.75,1.0f);

	if(!player.LoadPLG("tank2.plg", vscale, vpos, vrot,D3DCOLOR_XRGB(150,150,150)))
		return 1;
	vscale.Set(1.0f,2.0f,1.0f,1.0f);
	if(!tower.LoadPLG("tower.plg", vscale, vpos, vrot, D3DCOLOR_XRGB(255,200,255)))
		return 1;
	vscale.Set(3.0f,3.0f,3.0f,1.0f);
	if(!marker.LoadPLG("marker.plg", vscale, vpos, vrot, D3DCOLOR_XRGB(100,100,100)))
		return 1;

	int index;

	for(index = 0; index < num_tanks; index++) {
		tank_points[index].x = float(mx3d::rrand(-uni_rad, uni_rad));
		tank_points[index].y = 0;
		tank_points[index].z = float(mx3d::rrand(-uni_rad, uni_rad));
		tank_points[index].w = float(mx3d::rrand(0,360));
	}

	for(index = 0; index < num_towers; index++) {
		tower_points[index].x = float(mx3d::rrand(-uni_rad, uni_rad));
		tower_points[index].y = 0;
		tower_points[index].z = float(mx3d::rrand(-uni_rad, uni_rad));
	}
	return 0;
}


int init() {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
		return -1;
	front = SDL_SetVideoMode(480,272,0,0);
	max_clip_x = front->w;
	max_clip_y = front->h;
	stick = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);
	return 0;
}




void proc_axis() {
/*
 0 Triangle
 1 Circle
 2 Cross
 3 Square
 4 Left trigger
 5 Right trigger
 6 Down
 7 Left
 8 Up
 9 Right
10 Select
11 Start
12 Home
13 Hold*/
	/*
	32768 to 32767 */
	if(SDL_JoystickGetButton(stick, 8)) { // up
		cam.pos.x += tank_speed*mx3d::fast_sinf(cam.dir.y);
		cam.pos.z += tank_speed*mx3d::fast_cosf(cam.dir.y);
	}

	if(SDL_JoystickGetButton(stick, 6)) { // down
		cam.pos.x -= tank_speed*mx3d::fast_sinf(cam.dir.y);
		cam.pos.z -= tank_speed*mx3d::fast_cosf(cam.dir.y);
	}

	if(SDL_JoystickGetButton(stick, 9)) { // right
		cam.dir.y += 3;
		if((turning += 2) > 15)
			turning = 15;

	}
	
	if(SDL_JoystickGetButton(stick, 7)) { // left
		cam.dir.y -= 3;
		if((turning -= 2) < -15)
			turning = -15;
	}
	else {

		if(turning > 0)
			turning -= 1;
		else if(turning < 0)
			turning += 1;
	}


}

extern "C" int SDL_main(int argc, char **argv) {
	init();
	if(Init())
		printf("Error\n");


	SDL_Event e;
	int active = 1;

	while(active == 1) {
		SDL_FillRect(front, 0,0);
		render(0);
		SDL_UpdateRect(front, 0,0,front->w, front->h);
		if(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					active = 0;
					break;
				case SDL_JOYAXISMOTION:
					{
						memset(axis, 0, sizeof(axis));
						axis[e.jaxis.axis] = e.jaxis.value;
						proc_axis();

					}
					break;
					
			}
		}
	}
	SDL_FreeSurface(front);
	SDL_JoystickClose(stick);
	SDL_Quit();
	return 0;
}