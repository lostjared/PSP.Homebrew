#include "thehead.h"

int score = 0, miss = 0;


void init_buffer(struct array_buffer *buffer, int type) {
	buffer->next = 0;
	buffer->active = 1;
	buffer->type = type;
	switch(type) {
		case 1:
			buffer->x = rand()%640-cd->w;
			if(buffer->x < 0)
				buffer->x = 0;
			buffer->y = 0;
			
			break;
		case 2:
			buffer->x = the_can.x+(cannon->w/2)-15;
			buffer->y = 480-cannon->h-coin->h;
			break;
	}
}

struct array_buffer *add_item_to_buffer(struct array_buffer *node, int type) {


	struct array_buffer **ptr, *p;
	p = node;

	if(p == 0) {
		p = (struct array_buffer*) malloc ( sizeof(struct array_buffer) );
		init_buffer(p, type);
		return p;
	}

	ptr = &p;
	while( (p = *ptr) != 0) { ptr = &p->next; }
	// cycle through list
	p = (struct array_buffer*) malloc ( sizeof(struct array_buffer) );
	*ptr = p;
	init_buffer(p, type);
	return p;

}

void free_nodes(struct array_buffer *node) {

	if(node) {
		free_nodes(node->next);
		free(node);
	}
}

void dump_nodes(struct array_buffer *node) {
	if(node) {
		dump_nodes(node->next);
		printf("%d %d\n", node->x, node->y);
	}
}

void reset_node(struct array_buffer *node) {
	if(node->type == 1) {
		node->x = rand()%640-cd->w;
		if(node->x < 0) node->x = 0;
		node->y = 0;
		node->active = 1;
		
	}
	else {
		node->x = node->y = node->active = 0;
	}
}

int col_detect(SDL_Rect *rc2, SDL_Rect *rc1) {

	if(rc1->x <= rc2->w && rc1->x >= rc2->x && rc1->y <= rc2->h && rc1->y >= rc2->y) {
		return 1;
	}
	return 0;
}

void game_over() {
	screen = 1;
}

void proc_node(struct array_buffer *node) {
	static int counter = 0;
	SDL_Rect rc = { node->x, node->y, node->x + cd->w, node->y + cd->h };
	SDL_SetColorKey(cd, SDL_SRCCOLORKEY, SDL_MapRGB(front->format, 255, 0, 255) );
	SDL_BlitSurface(cd, 0, front, &rc);

		if((node->y+=10) > 480-cd->h) {
			reset_node(node);
			miss++;
			if(miss > 10)
				game_over();
		}
		counter = 0;
}

void proc_pnode(struct array_buffer *node) {
	SDL_Rect rc = { node->x, node->y, node->x + coin->w, node->y + coin->h };
	SDL_SetColorKey(coin, SDL_SRCCOLORKEY, SDL_MapRGB(front->format, 255,255, 255) );
	if(node->active == 1) {
		SDL_BlitSurface(coin, 0, front, &rc);

			if((node->y-=10) < 0) {
				node->active = 0;
				node->y = 0;
			}
		
	}
}

void node_logic(struct array_buffer *node) {

	struct array_buffer *ptr = node;
	for(ptr = node; ptr != 0; ptr = ptr->next) {
		if(ptr->type == 1 && ptr->active == 1) {
			struct array_buffer *pptr;
			for(pptr = node; pptr != 0; pptr = pptr->next) {
				if(pptr->type == 2 && pptr->active == 1) {
					SDL_Rect rc = { ptr->x, ptr->y, cd->w+ptr->x, cd->h+ptr->y };
					SDL_Rect rc2 = { pptr->x, pptr->y, coin->w+pptr->x, pptr->y+coin->h };
					if(col_detect(&rc,&rc2) == 1) {
						reset_node(ptr);
						pptr->active = 0;
						score ++;
					}
				}
			}
		}
	}

}

void proccess_nodes(struct array_buffer *node) {

	struct array_buffer *p;
	
	for(p = node; p != 0; p = p->next) {

		switch(p->type) {
			case 1:
					proc_node(p);
				break;
			case 2:
					proc_pnode(p);
				break;
		}
	}

	node_logic(node);
}


void rls_cash(struct array_buffer *node) {
	struct array_buffer *ptr , **p;
	int counter = 0;

	p = &node;

	while ((ptr = *p) != 0) {
		if(ptr->type == 2 && ptr->active == 0) {
			init_buffer(ptr, 2);
			return;
		} else if(ptr->type == 2) counter++;
		p = &ptr->next;
	}

	if(counter < 20) {
		ptr = (struct array_buffer*)malloc(sizeof(struct array_buffer));
		init_buffer(ptr, 2);
		*p = ptr;
	}

}

void new_game() {
	struct array_buffer *p;
	score = miss = screen = 0;
	for(p = buff; p != 0; p = p->next) {
		if(p->type == 1) {
			reset_node(p);
			p->active = 0;
		}
		else p->active = 0;
	}
}