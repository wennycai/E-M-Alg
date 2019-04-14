#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"
#include "rdtsc.h"

void test()
{
	//init_p("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaafffaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaafff");
	//bigint x, y, t;
	//init_str(x, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	//init_str(y, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	init_p("7");
	bigint x, y, t;
	init_m(x, y, t);
	int64 t0, t1;
	set_int(x, 1);
	set_int(y, 3);
	t0 = rdtsc();
	mul(t, x, y);
	t1 = rdtsc();
	print(t);
	printf("Time: %llu\n", t1 - t0);
}

int main()
{
	//init_p("3fffffffffffffffffffe00000000000000000000400000000000000000000007fffffffffffffffffffe00000000000000000000000000000000000000000004000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	//bigint x, y, t;
	//init_str(x, "ffffffffffffffffffffc0000000000000000000000000000000000000000001");
	//init_str(y, "14");
	//int64 t0, t1;
	//t0 = rdtsc();
	//power(x, x, y);
	//t1 = rdtsc();
	//print(t);
	//printf("Time: %llu\n", t1 - t0);
	test();
	return 0;
}

//compute tate pairing by Elliptic Net in Magma Style
// devised by Chang-an Zhao according to Stange's algorithm
//  Combining the idea of Chen Binglong(updating W(2i+2) by [W(2i-2), W(2i-1), W(2i), W(2i+1)]
// and the idea of Zhao Chang-an( A block only have SEVEN+THREE components)

//In this algorithm, we compute the self-pairing by using the Elliptic Net algorithm.


//Pairing computation on curves with embedding degree 1.
//These curves were first found by Koblitz and Menezes.
// set the parameters of elliptic curves over finite fields
// initial the parameters
//clear;
//
//
//// r is the order of point P
//r: = 2 ^ 256 - 2 ^ 174 + 1;
void translate()
{
//p: = 2 ^ 3202 - 2 ^ 3121 + 2 ^ 3038 + 2 ^ 2947 - 2 ^ 2865 + 2 ^ 2690 + 1;
	init_p("3fffffffffffffffffffe00000000000000000000400000000000000000000007fffffffffffffffffffe00000000000000000000000000000000000000000004000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	bigint r;
	init_str(r, "ffffffffffffffffffffc0000000000000000000000000000000000000000001");
	//finalexp: = Ceiling((p - 1) / r);
	//
	//
	//F: = GF(p);
	//
	//
	//
	//A: = F!(-1);
	//B: = F!0;
	//E: = EllipticCurve([F | A, B]);
	//
	//h: = 2 ^ 1345;
	//
	//P: = E![2820986207954827045364420606164325722142227654152620908552987871618385435055516001221784858097491501694378079789541140140059663605557811145596690410141754816207005150893923360607216882636521291202651533538070085173609255494929982439480994127959600426519014278391987881910722976089726332973582426254982445600042362175304182330508017260093439185312817123232289378706403554092537316146539818717970384615295461241736894393746128401910883857754298711542355763664769409576350034046691029957945872415235292636364672822742304520963704179484584462224826189933987735426036271805418922682297262059078083929829035755418391624378955789735553421987803243941987834465873122669612968923124954820534808247146018307241237834438590207156997624537422190798716000217627386527383039247932192776608882190641492825970738549540319020554179157595823964286232970877137105915120907458425324051996482070604410118909712887975122740967524170247136516679512245280026980260908830270662356158154569, 1561685103570150105474857628232210738930029001269772979821854169585839626382317958238686731472469961394107284867306999090047371616779681943606266716264283418285184310257076838427304059672678654804074568597012585983063752911533487654299150417682393158638795313153892546939454044451109613214771472654326237042840879781487328940622489880854290952712218905318802474038273130396865491945661650478495139262779130260348916917928431596002228738346582193720490740047940578894995974585031532585011975913809038072676667828267818503333647787609633097481289132536449665066938182748265498272221401817319972651218335889751724784905746709565660719632981428544052007890164762906600098854088088073473629969656887824730516742210283149994931159618350997582595300106201708166802824577994447114089438902661852728612193961142010765492605270788422868024912816981345638630293482306674450026770122921776093375180294081758125890811494257142735607194132813785090827021730960292486327004974642, 1];
	//
	//P: = (h)* P;
	//
	//basepoint: = P;
	//
	//// convert a positive integer in NAF form
	//// The first place of the sequence will store the least significant digit
	//convertNAF: = function(n)
	//	num : = n;
	//		str: = [];
	//			while num gt 0 do
	//				if IsOdd(num) then
	//					z : = 2 - (num mod 4);
	//		str: = Append(str, z);
	//				else
	//					z : = 0;
	//		str: = Append(str, z);
	//			end if;
	//		num: = Ceiling((num - z) / 2);
	//			end while;
	//			return str;
	//			end function;
	//
	//		bitstring_r: = convertNAF(r);
	//
	//
	//
	//			//this is the original doubleadd function
	//		doubleadd: = function(V, inverse_20, add);
	//			// the variable storing the current block
	//		currentV: = V;
	//			//create the output block
	//			//V := [ F |0, 0, 0, 0, 0, 0, 0, 0];
	//			//create temp variable
	//		S: = [F | 0, 0, 0, 0, 0, 0];
	//		T: = [F | 0, 0, 0, 0, 0, 0];
	//
	//			//initial data contains the precomputed inverses
	//			for k : = 1  to 6 do
	//				S[k] : = currentV[k + 1] ^ 2;
	//			T[k] : = currentV[k] * currentV[k + 2];
	//			end for;
	//
	//			if (add eq 0) then
	//				for i : = 1 to 4 do
	//					V[2 * i - 1] : = S[i] * T[i + 1] - S[i + 1] * T[i];
	//			V[2 * i]      : = (S[i] * T[i + 2] - S[i + 2] * T[i]) * inverse_20;
	//			end for;
	//			else
	//				for i : = 1 to 4 do
	//					V[2 * i - 1] : = (S[i] * T[i + 2] - S[i + 2] * T[i]) * inverse_20;
	//			V[2 * i]      : = S[i + 1] * T[i + 2] - S[i + 2] * T[i + 1];
	//			end for;
	//			end if;
	//			return V;
	//			end function;
	//
	//			//Improved doubleadd function 
	//			//this double_add function only requires SEVEN vectors in the iteration loop and so
	//			//saves 4M compared to the original doubleadd function
	//		Imdoubleadd: = function(V, initial_data, add);
	//			// the variable storing the current block
	//		currentV: = V;
	//		w2: = initial_data[2];
	//		w13: = initial_data[1];
	//			//create the output block
	//			//V := [ F |0, 0, 0, 0, 0, 0, 0, 0];
	//			//create temp variable
	//		S: = [F | 0, 0, 0, 0, 0, 0];
	//		T: = [F | 0, 0, 0, 0, 0, 0];
	//
	//			//initial data contains the precomputed inverses
	//			for k : = 1  to 6 do
	//				S[k] : = currentV[k + 1] ^ 2;
	//			T[k] : = currentV[k] * currentV[k + 2];
	//			end for;
	//
	//			if (add eq 0) then
	//				for i : = 1 to 3 do
	//					V[2 * i - 1] : = S[i] * T[i + 1] - S[i + 1] * T[i];
	//			V[2 * i]      : = (S[i] * T[i + 2] - S[i + 2] * T[i]) * initial_data[3];
	//			end for;
	//			V[7] : = S[4] * T[5] - S[5] * T[4];
	//			else
	//				for i : = 1 to 3 do
	//					V[2 * i - 1] : = (S[i] * T[i + 2] - S[i + 2] * T[i]) * initial_data[3];
	//			V[2 * i]      : = S[i + 1] * T[i + 2] - S[i + 2] * T[i + 1];
	//			end for;
	//		t1: = V[4] * V[6];
	//		t2: = V[5] ^ 2;
	//		t3: = V[3];
	//			V[7] : = (t1 * w2 - t2 * w13) / t3;
	//			end if;
	//			return V;
	//			end function;
	//
	//			//Improved doubleadd function 
	//			//this double_add function only requires SEVEN vectors in the iteration loop and so
	//			//saves 4M compared to the original doubleadd function
	//		Imdoubleadd2: = function(V, initial_data, add);
	//			// the variable storing the current block
	//		currentV: = V;
	//		w2: = initial_data[2];
	//		w13: = initial_data[1];
	//			//create the output block
	//			//V := [ F |0, 0, 0, 0, 0, 0, 0, 0];
	//			//create temp variable
	//		S: = [F | 0, 0, 0, 0, 0, 0];
	//		T: = [F | 0, 0, 0, 0, 0, 0];
	//
	//			//initial data contains the precomputed inverses
	//			for k : = 1  to 6 do
	//				S[k] : = currentV[k + 1] ^ 2;
	//			T[k] : = currentV[k] * currentV[k + 2];
	//			end for;
	//
	//			if (add eq 0) then
	//				for i : = 1 to 3 do
	//					V[2 * i - 1] : = S[i] * T[i + 1] - S[i + 1] * T[i];
	//			V[2 * i]      : = (S[i] * T[i + 2] - S[i + 2] * T[i]) * initial_data[3];
	//			end for;
	//			V[7] : = S[4] * T[5] - S[5] * T[4];
	//			else if (add eq 1) then
	//				for i : = 1 to 3 do
	//					V[2 * i - 1] : = (S[i] * T[i + 2] - S[i + 2] * T[i]) * initial_data[3];
	//			V[2 * i]      : = S[i + 1] * T[i + 2] - S[i + 2] * T[i + 1];
	//			end for;
	//		t1: = V[4] * V[6];
	//		t2: = V[5] ^ 2;
	//		t3: = V[3];
	//			// the following is to use the "homogeneous" properties of ellipticnets
	//			V[7] : = (t1 * w2 - t2 * w13);
	//			for i : = 1 to 6 do
	//				V[i] : = V[i] * t3;
	//			end for;
	//			else // correspond to add eq -1 
	//				for i : = 1 to 3 do
	//					V[2 * i] : = S[i] * T[i + 1] - S[i + 1] * T[i];
	//			V[2 * i + 1] : = (S[i] * T[i + 2] - S[i + 2] * T[i]) * initial_data[3];
	//			end for;
	//		t1: = V[4] * V[2];
	//		t2: = V[3] ^ 2;
	//		t3: = V[5];
	//			// the following is to use the "homogeneous" properties of ellipticnets
	//			V[1] : = (t1 * w2 - t2 * w13);
	//			for i : = 2 to 7 do
	//				V[i] : = V[i] * t3;
	//			end for;
	//			end if;
	//			end if;
	//			return V;
	//			end function;
	//
	//
	//			//this is the original Elliptic Net algorithm for self-pairing given by Stange
	//			//the cost will require 26M + 6S for each Doubling step. In fact, we only need to
	//			//consider the Doubling step for self-pairing since the order r is often with low 
	//			//Hamming weight
	//		selfpairing: = function(bpoint, m)
	//			// determine the number of steps in the double-and-add loop
	//			string_m : = IntegerToSequence(m, 2);   // The lowest bit is stored in the first place in the seq.
	//
	//				 m_size: = #IntegerToString(m, 2);
	//				 x1: = bpoint[1];
	//				 y1: = bpoint[2];
	//
	//				 w1: = F!1; //w(1,0)
	//				 w2: = 2 * y1; //w(2,0)
	//				 w3: = 3 * x1 ^ 4 + 6 * A * x1 ^ 2 + 12 * B * x1 - A ^ 2;  //w(3,0)
	//				 w4: = 4 * y1 * (x1 ^ 6 + 5 * A * x1 ^ 4 + 20 * B * x1 ^ 3 - 5 * A ^ 2 * x1 ^ 2 - 4 * A * B * x1 - 8 * B ^ 2 - A ^ 3); //w(4,0)
	//
	//
	//				 a: = w2;
	//				 b: = w3;
	//				 c: = w4;
	//
	//				 V: = [F | -a, -1, 0, 1, a, b, c, a ^ 3 * c - b ^ 3];
	//
	//					 for i : = 1 to m_size - 1do
	//						 V : = doubleadd(V, 1 / a, string_m[m_size - i]);
	//					 end for;
	//
	//
	//					 return (V[6] / (V[5] * 2 * y1)) ^ finalexp;
	//					 end function;
	//
	//					 //this is the improved Elliptic Net algorithm for self-pairing given by Chang-An
	//					 //the cost will require 22M + 6S for each Doubling step. In fact, we only need to
	//					 //use SEVEN vectors in the iteration loop  and so  saves some multiplications. 
	//				 Imselfpairing: = function(bpoint, m)
	//					 // determine the number of steps in the double-and-add loop
	//
	//						//string_m := IntegerToSequence(m,2);   // The lowest bit is stored in the first place in the seq.
	//					 string_m : = bitstring_r;   // The lowest bit is stored in the first place in the seq.
	//							m_size: = #string_m;
	//							x1: = bpoint[1];
	//							y1: = bpoint[2];
	//
	//							w1: = F!1; //w(1,0)
	//							w2: = 2 * y1; //w(2,0)
	//							w3: = 3 * x1 ^ 4 + 6 * A * x1 ^ 2 + 12 * B * x1 - A ^ 2;  //w(3,0)
	//							w4: = 4 * y1 * (x1 ^ 6 + 5 * A * x1 ^ 4 + 20 * B * x1 ^ 3 - 5 * A ^ 2 * x1 ^ 2 - 4 * A * B * x1 - 8 * B ^ 2 - A ^ 3); //w(4,0)
	//
	//
	//							initial_data: = [w1 * w3, w2 ^ 2, 1 / w2];
	//
	//							a: = w2;
	//							b: = w3;
	//							c: = w4;
	//
	//							V: = [F | -a, -1, 0, 1, a, b, c, a ^ 3 * c - b ^ 3];
	//
	//								for i : = 1 to m_size - 1 do
	//									//Imdoubleadd function still involves the inverse. 
	//									//	V :=  Imdoubleadd(V, initial_data, string_m[m_size - i]);
	//
	//									//Imdoubleadd2 function does not  involve the inverse, but has 7 multiplications. 
	//									V : = Imdoubleadd2(V, initial_data, string_m[m_size - i]);
	//								end for;
	//
	//								//the following is to debug by using scalar multiplications
	//								/*
	//										xn :=  x1 - (V[3]*V[5])/V[4]^2;
	//										yn :=  (V[3]^2*V[6] - V[5]^2*V[2])/(4*y1*V[4]^3);
	//										return [xn,yn];
	//								*/
	//
	//								return (V[6] / (V[5] * 2 * y1)) ^ finalexp;
	//								end function;
	//
	//
	//								"The pairing result is non-degenerate ***",
	//									selfpairing(P, r) ne 1, "***";
	//
	//
	//								"Check the blinearity";
	//							s: = Random(1, r - 1);
	//								selfpairing(s * P, r) - selfpairing(P, r) ^ (s ^ 2);
	//
	//								"Check the r-th property";
	//								selfpairing(P, r) ^ r;
	//
	//								"the following is for checking improved algorithm for selfpairing";
	//
	//
	//							s: = Random(1, r - 1);
	//								/*
	//								Imselfpairing(P, s)[1] eq (s*P)[1];
	//
	//								Imselfpairing(P, s)[2] eq (s*P)[2];
	//
	//								*/
	//								"***********************************************************";
	//								"The pairing result for improved alg is non-degenerate ***",
	//									Imselfpairing(P, r) ne 1, "***";
	//
	//
	//								"Check the blinearity";
	//							s: = Random(1, r - 1);
	//								Imselfpairing(s * P, r) - Imselfpairing(P, r) ^ (s ^ 2);
	//
	//								"Check the r-th property";
									//Imselfpairing(P, r) ^ r;
}