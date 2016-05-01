The Secret to the game
is there will never be a time to press circle, however it will ask you to
Unless you press it only 3 times (1&1&1=3)
than once the end screen comes up press it 3 times agian
to unlock the visualization


maybe its better to explain in code


// code snipit:


               // 1   &  2   &     3    ==    4
enum { B_START, B_TRI, B_CROSS, B_CIRCLE, B_SQUARE, B_SELECT };


// another snippit

inline void shuffle_cards(Card *cardz) {

	unsigned int i, r;
	int card_types[3];

	memset(card_types, 0, sizeof(card_types));

	int off = 0;
		do {
			r = rand()%4;
			for(i = 0; i < 3; i++) {
				if(card_types[i] == 0)
				{
					int ok = 0;
					for(unsigned int i = 0; i < 3; i++) {
						if(card_types[i] != r) continue;
						else { ok = 1; break; }
					}

					if(ok == 0)
					{
						card_types[off++] = r;
						break;
					}
				}
			}

			if(off >= 3) break;

		} while ( 1 );

		for(i = 0; i < 3; i++) {
			cardz[i].card_type = card_types[i];
		}

		do { cur_card = rand()%4; } while ( cur_card == 0 );
		do { rand_card = rand()%4; } while ( rand_card == 0 );
}

// than the input down function

inline void input_down(int d) {


	switch(screen) {
		case SCR_GAME:
		if(shuffle == 1) return;
		if(cur_card == d && rand_card == cur_card) {
			screen = SCR_ANSWER;
			answer = 1;
		}
		else screen = SCR_ANSWER, answer = 0;

		if(d == B_CIRCLE)
		wrong++;
		break;
		case SCR_FOURT:
			{
				static int counter = 0;
				if(pyscho_active == 1) {
					if(d == B_CIRCLE)
					{
						counter++;
						if(counter >= 3) {
							screen = SCR_INT;

						}
					} else counter = 0;

				}
				else {
					new_game();
				}
			}
			break;
		}
}
