/* $Id: universe-definition.sl,v 1.8 2002/06/05 00:34:50 mkrohn5 Exp $ */

/* declare global game parameters */
rulesystem {
	/* The modules */
	module_fleet = "basic";
        module_item = "basic";
	module_race = "basic";                  
	module_subfleet = "basic";
	module_system = "basic";

	/* The rule atoms */
	fleet_engine_failure = "basic";
        fleet_movement = "basic";
}

player {
	linkable = {
		id = [ff,00,00,00,00,01];
	}
	name = "Marco";
}

player {
	linkable = {
		id = [ff,00,00,00,00,02];
	}
	name = "Alberto";
}

race {
	race_base = {
		linkable = {
			id = [ff,00,00,00,01,00];
		}
		name = "Marconians";
		controller_link = [ff,00,00,00,00,01];
	}
	/** AR=0, CA=1, */
	prt = int2(1);
	lrt = false;         
	lrt = true;         
	lrt = false;       
}

race {
	race_base = {
		linkable = {
			id = [ff,00,00,00,02,00];
		}
		name = "Albertians";
		controller_link = [ff,00,00,00,00,02];
	}
        /** AR=0, CA=1, */
        prt = int2(2);
        lrt = false;         /* ARM   */
        lrt = true;          /* CE    */
        lrt = true;          /* IFE   */
}


item { 
	/* defines the type of the item (armor, stl-engine, ...) */  
	subblocktype = int2( 1 ); 
	item_base = {
		linkable = {
			id = [01,00,00,00,00,01];
		}
		item_name = "Long Leg";
		item_techlevel = int2( 5 );
		item_mass = int2( 100 );
		item_volume = int2( 120 );
                item_surface = int2( 20 );
	}
	stl_engine_power = int2( 5 );
} 

game {
	name = "The Stellar Legacy test game";
	galaxy_size = vec3d(100., 100., 0.);
	galaxy_systems = 10;
}

