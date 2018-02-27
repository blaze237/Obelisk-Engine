#pragma once

//Utility helper struct for working with colour values
struct Colour {
		Colour(float r, float g, float b, float a)
			:r(r), g(g), b(g), a(a)
		{}
	
		//Colour channel values
		float r, g, b, a;
	};