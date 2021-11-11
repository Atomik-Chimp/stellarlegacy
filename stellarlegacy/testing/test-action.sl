/* $Id: test-action.sl,v 1.3 2001/06/19 21:06:32 ishark Exp $ */

player_orders "Humanoids" {
	action {00,00,00,00,01,00} "Set Waypoint" {
		actor = {00,00,00,01,00,00};
		destination = {00,00,00,02,00,00};
		warp = 9;
	}
	action {00,00,00,00,02,00} "Set Waypoint" {
		actor = {00,00,00,02,00,00};
		destination = (10,20);
		warp = 5;
	}
}
