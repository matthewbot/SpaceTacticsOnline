ent_ship_base {
	type entity_base

	pos_main {
		type position
	}
	
	spr_main {
		type sprite
		position_c pos_main
		render_s ships
	}
	
	mot_main {
		type motion
		
		position_c pos_main
		
		tick_s motion
	}
	
	thrust_main {
		type thruster
		
		motion_c mot_main
		tick_s motion
	}
	
	input_main {
		type input
		
		thruster_c thrust_main
	}
	
	serial_main {
		type serialize
		
		partial {
			mot_main on
			thrust_main on
		}
		
		full {
			pos_main on
		}
	}
}
