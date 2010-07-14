ent_scout {
	type entity
	inherit ent_ship_base
	
	spr_main {
		spritetype light
		
		sprite_r spr_scout
	}
	
	thrust_main {
		default {
			rotaccel 30
			rotmaxspeed 8
			rotbrake 40
		
			accel 2000
			maxspeed 100
			brake 3000
		}
		
		brake {
			rotaccel 2
			rotmaxspeed 4
			rotbrake 4
		
			accel 700
			maxspeed 200
			brake 700
		}
		
		cruise {
			rotaccel 4
			rotmaxspeed 7
			rotbrake 4
		
			accel 800
			maxspeed 600
			brake 800
		}
		
		accel {
			rotaccel 2
			rotmaxspeed 4
			rotbrake 2
		
			accel 1800
			maxspeed 1400
			brake 1300
		}
	}
}
