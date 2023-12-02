#include "easing_functions.h"
#include <math.h>
#define PI          3.1415926535897932384626433832795
/*
reference: https://blog.csdn.net/z2014z/article/details/120691794

*/

void easing_fun_linear(anime_parms_t * parms) {
	parms->val = (parms->val_target - parms->val_begin) * parms->passed_time / parms->duration + parms->val_begin;
}

void easing_fun_OutQuad(anime_parms_t* parms) {
	float t, b, c, d;
	t = parms->passed_time;
	b = parms->val_begin;
	c = parms->val_target - parms->val_begin;
	d = parms->duration;
	if ((t /= d / 2) < 1) {
	
		parms->val = c / 2 * t * t + b;
	}
	else {
		--t;
		parms->val = -c / 2 * ((t) * (t - 2) - 1) + b;
	}
}

void easing_fun_InElastic(anime_parms_t* parms) {
	float t, b, c, d;
	t = parms->passed_time;
	b = parms->val_begin;
	c = parms->val_target - parms->val_begin;
	d = parms->duration;
	float s = 1.70158;
	float p = 0;
	float a = c;
	if (t == 0)
	{
		parms->val = b;
		return;
	}
	if ((t /= d) == 1)
	{
		parms->val = b + c;
		return;
	}
	if (!p) p = d * .3;
	if (a < fabs(c)) {
		a = c;
		s = p / 4;
	}
	else { 
		s = p / (2 * PI) * asin(c / a);
	}
	t-=1;
	parms->val =  -(a * pow(2, 10 * (t)) * sin((t * d - s) * (2 * PI) / p)) + b;
}


static float easeOutBounce(float t, float b, float c,float d) {
	if ((t /= d) < (1 / 2.75)) {
		return c * (7.5625 * t * t) + b;
	}
	else if (t < (2 / 2.75)) {
		t -= (1.5 / 2.75);
		return c * (7.5625 * (t) * t + .75) + b;
	}
	else if (t < (2.5 / 2.75)) {
		t -= (2.25 / 2.75);
		return c * (7.5625 * (t) * t + .9375) + b;
	}
	else {
		t -= (2.625 / 2.75);
		return c * (7.5625 * (t) * t + .984375) + b;
	}
}

void easing_fun_OutBounce(anime_parms_t* parms) {
	float t, b, c, d;
	t = parms->passed_time;
	b = parms->val_begin;
	c = parms->val_target - parms->val_begin;
	d = parms->duration;
	parms->val = easeOutBounce(t,b,c,d);
}


void easing_fun_InBounce(anime_parms_t* parms) {
	float t, b, c, d;
	t = parms->passed_time;
	b = parms->val_begin;
	c = parms->val_target - parms->val_begin;
	d = parms->duration;
	parms->val =  c - easeOutBounce(d - t, 0, c, d) + b;
}

void easing_fun_InOutBounce(anime_parms_t* parms) {
	//if (t < d / 2) return easeInBounce(t * 2, 0, c, d) * .5 + b;
	//return easeOutBounce(t * 2 - d, 0, c, d) * .5 + c * .5 + b;
}
