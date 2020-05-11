#include <algorithm>
#include "fuzzylogic.h"

/////////////////////////////////////////////////////////////////

//Initialise Fuzzy Rules

void initFuzzyRules(fuzzy_system_rec *fl) {
	
   const int
      no_of_rules = fl->no_of_inp_regions;
   
   int i;
	
//---------------------------------------------------------------------------- 	
//THETA vs. THETA_DOT	
//   
   for (i = 0;i < no_of_rules;i++) {
      //both inputs are added together in the equation Y = A*theta + B * theta_dot
       fl->rules[i].inp_index[0] = theta_emergency;
       fl->rules[i].inp_index[1] = x_emergency;
       fl->rules[0].out_fuzzy_set = out_ze;
   }
      
   /* Regions for theta emergence and x emergence: */
   //if both are negatively large, output NL
   fl->rules[0].inp_fuzzy_set[0] = in_nl;
   fl->rules[0].inp_fuzzy_set[1] = in_nl;
   fl->rules[0].out_fuzzy_set = out_nl;

   //if both are negatively small, output negatively medium
   fl->rules[1].inp_fuzzy_set[0] = in_ns;
   fl->rules[1].inp_fuzzy_set[1] = in_ns;
   fl->rules[1].out_fuzzy_set = out_nm;

   //if both are zero, output zero
   fl->rules[2].inp_fuzzy_set[0] = in_ze;
   fl->rules[2].inp_fuzzy_set[1] = in_ze;
   fl->rules[2].out_fuzzy_set = out_ze;

   //if both are positively small, output positively medium
   fl->rules[3].inp_fuzzy_set[0] = in_ps;
   fl->rules[3].inp_fuzzy_set[1] = in_ps;
   fl->rules[3].out_fuzzy_set = out_pm;

   //if both are positively large, output PL
   fl->rules[4].inp_fuzzy_set[0] = in_pl;
   fl->rules[4].inp_fuzzy_set[1] = in_pl;
   fl->rules[4].out_fuzzy_set = out_pl;

   //if theta emergence is PL and x emergence is zr, output PM
   fl->rules[5].inp_fuzzy_set[0] = in_pl;
   fl->rules[5].inp_fuzzy_set[1] = in_ze;
   fl->rules[5].out_fuzzy_set = out_pm;

   //if theta emergence is PL and x emergence is NL output PS
   fl->rules[6].inp_fuzzy_set[0] = in_pl;
   fl->rules[6].inp_fuzzy_set[1] = in_nl;
   fl->rules[6].out_fuzzy_set = out_ps;

   //if theta emergence is PS and x emergence is NS, output ps
   fl->rules[7].inp_fuzzy_set[0] = in_ps;
   fl->rules[7].inp_fuzzy_set[1] = in_ns;
   fl->rules[7].out_fuzzy_set = out_ps;

   //if theta emergence is zero and x emergence is PL, output ps
   fl->rules[8].inp_fuzzy_set[0] = in_ze;
   fl->rules[8].inp_fuzzy_set[1] = in_pl;
   fl->rules[8].out_fuzzy_set = out_ps;

   //if theta emergence is zr and x emergence is NL output NS
   fl->rules[9].inp_fuzzy_set[0] = in_ze;
   fl->rules[9].inp_fuzzy_set[1] = in_nl;
   fl->rules[9].out_fuzzy_set = out_ns;

   //if theta emergence is NS and x emergence is PS output NS
   fl->rules[10].inp_fuzzy_set[0] = in_ns;
   fl->rules[10].inp_fuzzy_set[1] = in_ps;
   fl->rules[10].out_fuzzy_set = out_ns;

   //if theta emergence is NL and x emergence is PL, output NS
   fl->rules[11].inp_fuzzy_set[0] = in_nl;
   fl->rules[11].inp_fuzzy_set[1] = in_pl;
   fl->rules[11].out_fuzzy_set = out_ns;

   //if theta emergence is NL and X emergence is ZE, output NM
   fl->rules[12].inp_fuzzy_set[0] = in_nl;
   fl->rules[12].inp_fuzzy_set[1] = in_ze;
   fl->rules[12].out_fuzzy_set = out_nm;

   //outputRules end
   
	
   





      return;
}


void initMembershipFunctions(fuzzy_system_rec *fl) {
	//copy from here 
   // fl->inp_mem_fns[x_emergency][in_ze] = init_trapz (-1.5,-0.5,0,0,left_trapezoid);
   //~ fl->inp_mem_fns[in_x][in_ze] = init_trapz (-1.5,-0.5,0.5,1.5,regular_trapezoid);
   //~ fl->inp_mem_fns[in_x][in_pos] = init_trapz (0.5,1.5,0,0,right_trapezoid);
	
   /* The X membership functions */
   float a,b,c,d; // numbers to play with membership proportions easily.
   a = 2.0;
   b = 2.0;
   c = 2.0;
   d = 2.0;
   fl->inp_mem_fns[x_emergency][in_nl] = init_trapz (c*-0.5,d*-0.25,0,0,left_trapezoid);
   fl->inp_mem_fns[x_emergency][in_ns] = init_trapz (a*-0.5,b*-0.25,c*-0.25,d*0,regular_trapezoid);
  	fl->inp_mem_fns[x_emergency][in_ze] = init_trapz (a*-0.25,b*0,c*0,d*0.25,regular_trapezoid);
   fl->inp_mem_fns[x_emergency][in_ps] = init_trapz (a*0,b*0.25,c*0.25,d*0.5,regular_trapezoid);
   fl->inp_mem_fns[x_emergency][in_pl] = init_trapz (a*0.25,b*0.5,c*0,d*0,right_trapezoid);
   
	
   /* The theta emergence membership */
   //enter the appropriate membership function initialisations here 
  	a = 1.0;
   b = 1.0;
   c = 1.0;
   d = 1.0;
   fl->inp_mem_fns[theta_emergency][in_nl] = init_trapz (c*-0.5,d*-0.25,0,0,left_trapezoid);
   fl->inp_mem_fns[theta_emergency][in_ns] = init_trapz (a*-0.5,b*-0.25,c*-0.25,d*0,regular_trapezoid);
  	fl->inp_mem_fns[theta_emergency][in_ze] = init_trapz (a*-0.25,b*0,c*0,d*0.25,regular_trapezoid);
   fl->inp_mem_fns[theta_emergency][in_ps] = init_trapz (a*0,b*0.25,c*0.25,d*0.5,regular_trapezoid);
   fl->inp_mem_fns[theta_emergency][in_pl] = init_trapz (a*0.25,b*0.5,c*0,d*0,right_trapezoid);

	
	
   return;
}

void initFuzzySystem (fuzzy_system_rec *fl) {

   //Note: The settings of these parameters will depend upon your fuzzy system design
   fl->no_of_inputs = 2;  /* Inputs are handled 1 at a time only */
   fl->no_of_rules = 25;
   fl->no_of_inp_regions = 5; //number of input regions per input
   fl->no_of_outputs = 1;
	
	
	//Sample only
	// fl->output_values [out_nvl]=-95.0;
	// fl->output_values [out_nl] = -85.0;
   fl->output_values [out_nl]=-125.0;
   fl->output_values [out_nm]=-75.0;
   fl->output_values [out_ns]=-30.0;
   fl->output_values [out_ze]=-0.0;
   fl->output_values [out_ps]=30.0;
   fl->output_values [out_pm]=75.0;
   fl->output_values [out_pl]=125.0;
   

   fl->rules = (rule *) malloc ((size_t)(fl->no_of_rules*sizeof(rule)));
   initFuzzyRules(fl);
   initMembershipFunctions(fl);
   return;
}

//////////////////////////////////////////////////////////////////////////////

trapezoid init_trapz (float x1,float x2,float x3,float x4, trapz_type typ) {
	
   trapezoid trz;
   trz.a = x1;
   trz.b = x2;
   trz.c = x3;
   trz.d = x4;
   trz.tp = typ;
   switch (trz.tp) {
	   
      case regular_trapezoid:
         	 trz.l_slope = 1.0/(trz.b - trz.a);
         	 trz.r_slope = 1.0/(trz.c - trz.d);
         	 break;
	 
      case left_trapezoid:
         	 trz.r_slope = 1.0/(trz.a - trz.b);
         	 trz.l_slope = 0.0;
         	 break;
	 
      case right_trapezoid:
         	 trz.l_slope = 1.0/(trz.b - trz.a);
         	 trz.r_slope = 0.0;
         	 break;
   }  /* end switch  */
   
   return trz;
}  /* end function */

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
float trapz (float x, trapezoid trz) {
   switch (trz.tp) {
	   
      case left_trapezoid:
         	 if (x <= trz.a)
         	    return 1.0;
         	 if (x >= trz.b)
         	    return 0.0;
         	 /* a < x < b */
         	 return trz.r_slope * (x - trz.b);
	 
	 
      case right_trapezoid:
         	 if (x <= trz.a)
         	    return 0.0;
         	 if (x >= trz.b)
         	    return 1.0;
         	 /* a < x < b */
         	 return trz.l_slope * (x - trz.a);
	 
      case regular_trapezoid:
         	 if ((x <= trz.a) || (x >= trz.d))
         	    return 0.0;
         	 if ((x >= trz.b) && (x <= trz.c))
         	    return 1.0;
         	 if ((x >= trz.a) && (x <= trz.b))
         	    return trz.l_slope * (x - trz.a);
         	 if ((x >= trz.c) && (x <= trz.d))
         	    return  trz.r_slope * (x - trz.d);
         	    
	 }  /* End switch  */
	 
   return 0.0;  /* should not get to this point */
}  /* End function */

//////////////////////////////////////////////////////////////////////////////
float max_of(float values[],int no_of_inps) {
   int i;
   float val;
   val = values [0];
   for (i = 1;i < no_of_inps;i++) {
       if (values[i] > val) val = values [i];
   }
   return val;
}



//////////////////////////////////////////////////////////////////////////////
float fuzzy_system (float inputs[],fuzzy_system_rec fz) {
   int i,j;
   short variable_index,fuzzy_set;
   float sum1 = 0.0,sum2 = 0.0,weight;
   float m_values[MAX_NO_OF_INPUTS];
	
   
   for (i = 0;i < fz.no_of_rules;i++) {
      for (j = 0;j < fz.no_of_inputs;j++) {
         variable_index = fz.rules[i].inp_index[j];
         fuzzy_set = fz.rules[i].inp_fuzzy_set[j];
         m_values[j] = trapz(inputs[variable_index],
	       fz.inp_mem_fns[variable_index][fuzzy_set]);
	   } /* end j  */
      
       weight = max_of (m_values,fz.no_of_inputs);
				
       sum1 += weight * fz.output_values[fz.rules[i].out_fuzzy_set];
       sum2 += weight;
   } /* end i  */
 
	
	if (fabs(sum2) < TOO_SMALL) {
      cout << "\r\nFLPRCS Error: Sum2 in fuzzy_system is 0.  Press key: " << endl;
      //~ getch();
      //~ exit(1);
      return 0.0;
   }
   
   return (sum1/sum2);
}  /* end fuzzy_system  */

//////////////////////////////////////////////////////////////////////////////
void free_fuzzy_rules (fuzzy_system_rec *fz) {
   if (fz->allocated){
	   free (fz->rules);
	}
	
   fz->allocated = false;
   return;
}

