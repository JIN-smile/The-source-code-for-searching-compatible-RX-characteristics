#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

void printhead()
{
    cout << "(set-logic QF_ABV)" << endl;
    cout << "(set-info :smt-lib-version 2.5)" << endl;
    cout << "(set-option :produce-models true)" <<endl;
}



void declare(int r)
{

    cout << "(declare-fun dk0 () (_ BitVec 16)) " <<endl;
    cout << "(declare-fun dk1 () (_ BitVec 16)) " <<endl;
    cout << "(declare-fun dk2 () (_ BitVec 16)) " <<endl;
    cout << "(declare-fun dk () (_ BitVec 16)) " <<endl;



    for(int i=1; i<=r; i++)
    {
        cout << "(declare-fun lft_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun rgt_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun key_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun d_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun varibits_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun doublebits_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun z_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun wr_" << i << " () (_ BitVec 16)) " <<endl;

    }


    cout << "(declare-fun lft_" << r+1 << " () (_ BitVec 16)) " ;
    cout << "(declare-fun rgt_" << r+1 << " () (_ BitVec 16)) " ;
    cout << endl;



    for(int i=1; i<=r; i++)
    {
        cout << "(declare-fun klft_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun krgt_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun c_" << i << " () (_ BitVec 16)) " <<endl;
    }

    cout << "(declare-fun klft_" << r+1 << " () (_ BitVec 16)) " ;
    cout << "(declare-fun krgt_" << r+1 << " () (_ BitVec 16)) " ;
    cout << endl;

    for(int i=1; i<=(r+2); i++)
    {
        cout << "(declare-fun value_k_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun value_kpie_" << i << " () (_ BitVec 16)) " <<endl;

    }

    for(int i=1; i<=r; i++)
    {
        cout << "(declare-fun value_key_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun value_keypie_" << i << " () (_ BitVec 16)) " <<endl;
    }


    cout << "(declare-fun value_dk0 () (_ BitVec 16)) " <<endl;
    cout << "(declare-fun value_dk1 () (_ BitVec 16)) " <<endl;
    cout << "(declare-fun value_dk2 () (_ BitVec 16)) " <<endl;
    cout << "(declare-fun value_dk () (_ BitVec 16)) " <<endl;


    cout << "(declare-fun value_dk0pie () (_ BitVec 16)) " <<endl;
    cout << "(declare-fun value_dk1pie () (_ BitVec 16)) " <<endl;
    cout << "(declare-fun value_dk2pie () (_ BitVec 16)) " <<endl;
    cout << "(declare-fun value_dkpie () (_ BitVec 16)) " <<endl;



    for(int i=1; i<=r; i++)
    {
        cout << "(declare-fun value_klft_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun value_krgt_" << i << " () (_ BitVec 16)) " <<endl;

        cout << "(declare-fun value_klftpie_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun value_krgtpie_" << i << " () (_ BitVec 16)) " <<endl;
    }


    for(int i=1; i<=(r+1); i++)
    {
        cout << "(declare-fun value_lft_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun value_rgt_" << i << " () (_ BitVec 16)) " <<endl;

        cout << "(declare-fun value_lftpie_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun value_rgtpie_" << i << " () (_ BitVec 16)) " <<endl;

        cout << "(declare-fun rxdiff_lft_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun rxdiff_rgt_" << i << " () (_ BitVec 16)) " <<endl;
        cout << "(declare-fun rxdiff_k_" << i << " () (_ BitVec 16)) " <<endl;
    }

    //define hamming weight
    cout <<"(define-fun w_H0 ((x (_ BitVec 16))) (_ BitVec 16)"<<endl;
    cout <<"      (bvadd (bvand x #x5555 )"<<endl;
    cout <<"             (bvand (bvlshr x #x0001) #x5555 )))"<<endl;
    cout <<"(define-fun w_H1 ((x (_ BitVec 16))) (_ BitVec 16)"<<endl;
    cout <<"      (bvadd (bvand x #x3333 )"<<endl;
    cout <<"             (bvand (bvlshr x #x0002) #x3333 )))"<<endl;
    cout <<"(define-fun w_H2 ((x (_ BitVec 16))) (_ BitVec 16)"<<endl;
    cout <<"      (bvadd (bvand x #x0f0f )"<<endl;
    cout <<"             (bvand (bvlshr x #x0004) #x0f0f)))"<<endl;
    cout <<"(define-fun w_H3 ((x (_ BitVec 16))) (_ BitVec 16)"<<endl;
    cout <<"      (bvadd (bvand x #x00ff )"<<endl;
    cout <<"             (bvand (bvlshr x #x0008) #x00ff )))"<<endl;
    cout <<"(define-fun w_H ((x (_ BitVec 16))) (_ BitVec 16) (w_H3 (w_H2 (w_H1 (w_H0 x)))))"<<endl;

}

void cczformula_delta(int r)
{

    //key schedule
    for(int i=1; i<=r;i++)
    {
        if((i == 1) || (i == 2) || (i == 3) || (i == 4)
           || (i == 5) || (i == 9) || (i == 10)||
           (i == 12) || (i == 13) || (i == 14) ||
           (i == 16) || (i == 18) || (i == 23) ||
           (i == 26) || (i == 28) || (i == 29) || (i == 32))
        {
            cout<< " (assert (= c_"<<i<<" #xfffd))"<<endl;
        }
        else
        {
            cout<< " (assert (= c_"<<i<<" #xfffc))"<<endl;
        }

    }

    //the first round
    cout<< " (assert (= krgt_1  (bvxor dk0 ((_ rotate_left 5) dk))))"<<endl;


    cout<< " (assert (= klft_1  (bvxor (bvxor (bvxor  ((_ rotate_left 1) c_1)  krgt_1)  c_1)  dk) ))"<<endl;


    //second round
    cout<< " (assert (= krgt_2  (bvxor dk1 ((_ rotate_left 5) krgt_1))))"<<endl;


    cout<< " (assert (= klft_2  (bvxor (bvxor (bvxor  ((_ rotate_left 1) c_1)  krgt_2)  c_1)  krgt_1) ))"<<endl;


    //third round
    cout<< " (assert (= krgt_3  (bvxor dk2 ((_ rotate_left 5) krgt_2))))"<<endl;


    cout<< " (assert (= klft_3  (bvxor (bvxor (bvxor  ((_ rotate_left 1) c_1)  krgt_3)  c_1)  krgt_2) ))"<<endl;


    for(int i=1; i<=(r-3);i++)
    {

        cout<< " (assert (= krgt_"<< i+3 <<"  (bvxor  klft_"<< i<<" ((_ rotate_left 5) krgt_"<< i+2 <<"))))"<<endl;

        cout<< " (assert (= klft_"<< i+3 <<"  (bvxor (bvxor (bvxor  ((_ rotate_left 1) c_1)  krgt_"<< i+3 <<")  c_1)  krgt_"<< i+2 <<") ))"<<endl;

    }



    //data part

    //the first round

    cout<< " (assert (= key_1  dk ))"<<endl;

    cout<< " (assert (= rgt_2  lft_1 ))"<<endl;

    cout<< " (assert (= varibits_1  (bvor  ((_ rotate_left 5) lft_1)  lft_1)))"<<endl;

    cout<< " (assert (= doublebits_1  (bvand  (bvand (bvxor ((_ rotate_left 5) lft_1) #xffff)  lft_1) ((_ rotate_left 10) lft_1))))"<<endl;

    cout<< " (assert (= #x0000 (bvand  (bvxor varibits_1 #xffff)  d_1))) "<<endl;

    cout<< " (assert (= #x0000 (bvand  (bvxor ((_ rotate_left 5) d_1) d_1) doublebits_1))) "<<endl;

    cout<< " (assert (= lft_2  (bvxor (bvxor rgt_1 d_1) (bvxor ((_ rotate_left 1) lft_1) key_1))))"<<endl;

    cout<< " (assert (= z_1 (bvxor varibits_1 doublebits_1)))"<<endl;



    for(int i = 1; i <= (r-1);i++)
    {
        cout<< " (assert (= key_"<<i+1<<"  krgt_"<<i<<"))"<<endl;

        cout<< " (assert (= rgt_"<< i+2 <<"  lft_"<< i+1<<" ))"<<endl;

        cout<< " (assert (= varibits_"<< i+1 <<"  (bvor  ((_ rotate_left 5) lft_"<< i+1 <<")  lft_"<< i+1 <<")))"<<endl;

        cout<< " (assert (= doublebits_"<< i+1 <<"  (bvand  (bvand (bvxor ((_ rotate_left 5) lft_"<< i+1 <<") #xffff)  lft_"<< i+1 <<") ((_ rotate_left 10) lft_"<< i+1 <<"))))"<<endl;

        cout<< " (assert (= #x0000 (bvand  (bvxor varibits_"<< i+1 <<" #xffff)  d_"<< i+1 <<"))) "<<endl;

        cout<< " (assert (= #x0000 (bvand  (bvxor ((_ rotate_left 5) d_"<< i+1 <<") d_"<< i+1 <<") doublebits_"<< i+1 <<"))) "<<endl;

        cout<< " (assert (= lft_"<< i+2 <<"  (bvxor (bvxor rgt_"<<i+1<<" d_"<<i+1<<") (bvxor ((_ rotate_left 1) lft_"<<i+1<<") key_"<<i+1<<"))))"<<endl;

        cout<< " (assert (= z_"<< i+1 <<" (bvxor varibits_"<< i+1 <<" doublebits_"<< i+1 <<")))"<<endl;

    }


}


void cczformula_value(int r)
{

    cout<< " (assert (= value_krgt_1  (bvxor value_dk0 ((_ rotate_left 5) value_dk))))"<<endl;


    cout<< " (assert (= value_klft_1  (bvxor (bvxor  value_krgt_1  c_1)  value_dk) ))"<<endl;


    //second round
    cout<< " (assert (= value_krgt_2  (bvxor value_dk1 ((_ rotate_left 5) value_krgt_1))))"<<endl;


    cout<< " (assert (= value_klft_2  (bvxor (bvxor  value_krgt_2  c_1)  value_krgt_1) ))"<<endl;


    //third round
    cout<< " (assert (= value_krgt_3  (bvxor value_dk2 ((_ rotate_left 5) value_krgt_2))))"<<endl;


    cout<< " (assert (= value_klft_3  (bvxor (bvxor  value_krgt_3  c_1 ) value_krgt_2)))"<<endl;


    for(int i=1; i<=(r-3);i++)
    {

        cout<< " (assert (= value_krgt_"<< i+3 <<"  (bvxor  value_klft_"<< i<<" ((_ rotate_left 5) value_krgt_"<< i+2 <<"))))"<<endl;

        cout<< " (assert (= value_klft_"<< i+3 <<"  (bvxor (bvxor  value_krgt_"<< i+3 <<"  c_1)  value_krgt_"<< i+2 <<") ))"<<endl;

    }


    //k'
    cout<< " (assert (= value_krgtpie_1  (bvxor value_dk0pie ((_ rotate_left 5) value_dkpie))))"<<endl;


    cout<< " (assert (= value_klftpie_1  (bvxor (bvxor  value_krgtpie_1  c_1)  value_dkpie) ))"<<endl;



    cout<< " (assert (= value_krgtpie_2  (bvxor value_dk1pie ((_ rotate_left 5) value_krgtpie_1))))"<<endl;


    cout<< " (assert (= value_klftpie_2  (bvxor (bvxor  value_krgtpie_2  c_1)  value_krgtpie_1) ))"<<endl;



    cout<< " (assert (= value_krgtpie_3  (bvxor value_dk2pie ((_ rotate_left 5) value_krgtpie_2))))"<<endl;


    cout<< " (assert (= value_klftpie_3  (bvxor (bvxor  value_krgtpie_3  c_1 ) value_krgtpie_2)))"<<endl;


    for(int i=1; i<=(r-3);i++)
    {

        cout<< " (assert (= value_krgtpie_"<< i+3 <<"  (bvxor  value_klftpie_"<< i<<" ((_ rotate_left 5) value_krgtpie_"<< i+2 <<"))))"<<endl;

        cout<< " (assert (= value_klftpie_"<< i+3 <<"  (bvxor (bvxor  value_krgtpie_"<< i+3 <<"  c_1)  value_krgtpie_"<< i+2 <<") ))"<<endl;

    }


    for(int i=1; i<=r;i++)
    {

        cout<< " (assert (= rxdiff_k_"<< i <<" (bvxor ((_ rotate_left 1) value_krgt_"<< i <<") value_krgtpie_"<< i <<")))"<<endl;


    }

    for(int i=1; i<=r;i++)
    {

        cout<< " (assert (= rxdiff_k_"<< i <<"  key_"<<i<<"))"<<endl;


    }



    //data part
    for(int i=1; i<=r;i++)
    {
        cout<< " (assert (= value_rgt_"<< i+1 <<"  value_lft_"<< i <<"))"<<endl;

        cout<< " (assert (= value_lft_"<< i+1 <<"  (bvxor (bvxor (bvxor (bvand ((_ rotate_left 5) value_lft_"<< i <<") value_lft_"<< i <<") ((_ rotate_left 1) value_lft_"<< i <<")) value_rgt_"<< i <<") value_k_"<< i <<")))"<<endl;

    }

    for(int i=1; i<=r;i++)
    {
        cout<< " (assert (= value_rgtpie_"<< i+1 <<"  value_lftpie_"<< i <<"))"<<endl;

        cout<< " (assert (= value_lftpie_"<< i+1 <<"  (bvxor (bvxor (bvxor (bvand ((_ rotate_left 5) value_lftpie_"<< i <<") value_lftpie_"<< i <<") ((_ rotate_left 1) value_lftpie_"<< i <<")) value_rgtpie_"<< i <<") value_kpie_"<< i <<")))"<<endl;

    }

    for(int i=1; i<=(r+1);i++)
    {

        cout<< " (assert (= rxdiff_lft_"<< i <<" (bvxor ((_ rotate_left 1) value_lft_"<< i <<") value_lftpie_"<< i <<")))"<<endl;
        cout<< " (assert (= rxdiff_rgt_"<< i <<" (bvxor ((_ rotate_left 1) value_rgt_"<< i <<") value_rgtpie_"<< i <<")))"<<endl;


    }

    for(int i=1; i<=(r+1);i++)
    {

        cout<< " (assert (= rxdiff_lft_"<< i <<"  lft_"<<i<<"))"<<endl;
        cout<< " (assert (= rxdiff_rgt_"<< i <<"  rgt_"<<i<<"))"<<endl;

    }
}



void objectivefun(int r, int bound_plain)
{


    for(int i=1; i<=r;i++)
    {
        cout<< " (assert (= wr_"<<i<<" (w_H z_"<<i<<")))"<<endl;
    }

    cout << " (assert (= ";

    for(int i=1; i<=r; i++)
    {
        if(i<r)
        {
            cout << "(bvadd  wr_"<<i<<" ";
        }

        else
        {
            cout << "wr_"<< r <<" ";
        }
    }

    for(int i=1; i<r; i++)
    {
        cout << ")";
    }

    cout <<" (_ bv"<<bound_plain<<" 16)))"<<endl;
}


void tail(int r)
{

	cout << "(check-sat)" << endl;

	for(int i=1;i<=(r+1);i++)
	{

	    cout << "(get-value (value_lft_"<< i <<"))" << endl;
	    cout << "(get-value (value_rgt_"<< i <<"))" << endl;

	    cout << "(get-value (value_lftpie_"<< i <<"))" << endl;
	    cout << "(get-value (value_rgtpie_"<< i <<"))" << endl;

	    cout << "(get-value (rxdiff_lft_"<< i <<"))" << endl;
	    cout << "(get-value (lft_"<< i <<"))" << endl;

	    cout << "(get-value (rxdiff_rgt_"<< i <<"))" << endl;
	    cout << "(get-value (rgt_"<< i <<"))" << endl;
	}


	for(int i=1;i<=r;i++)
	{

	    cout << "(get-value (value_klft_"<< i <<"))" << endl;
	    cout << "(get-value (value_klftpie_"<< i <<"))" << endl;

	    cout << "(get-value (value_krgt_"<< i <<"))" << endl;
	    cout << "(get-value (value_rgtpie_"<< i <<"))" << endl;

	    cout << "(get-value (rxdiff_k_"<< i <<"))" << endl;

	    cout << "(get-value (key_"<< i <<"))" << endl;
	}



	cout << "(get-value (dk0))" << endl;
	cout << "(get-value (dk1))" << endl;
	cout << "(get-value (dk2))" << endl;
	cout << "(get-value (dk))" << endl;

	for(int i=1;i<=r;i++)
	{

	    cout << "(get-value (klft_"<< i <<"))" << endl;
	    cout << "(get-value (krgt_"<< i <<"))" << endl;
	}



	for(int i=1;i<=r;i++)
	{

	    cout << "(get-value (lft_"<< i <<"))" << endl;
	    cout << "(get-value (rgt_"<< i <<"))" << endl;
	    cout << "(get-value (key_"<< i <<"))" << endl;
	    cout << "(get-value (d_"<< i <<"))" << endl;
	    cout << "(get-value (z_"<< i <<"))" << endl;
	    cout << "(get-value (wr_"<< i <<"))" << endl;


	}

	cout << "(get-value (lft_"<< r+1 <<"))" << endl;
    cout << "(get-value (rgt_"<< r+1 <<"))" << endl;

	cout << "(exit)" << endl;


}

int main(int argc, char** argv)
{
    int ROUND = atoi(argv[1]);
    int BOUND_PLAIN = atoi(argv[2]);
    printhead();

    declare(ROUND);

    cczformula_delta(ROUND);
    cczformula_value(ROUND);

    objectivefun(ROUND,BOUND_PLAIN);

    tail(ROUND);

    return 0;
}






