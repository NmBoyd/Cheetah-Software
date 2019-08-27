function [row_index_initial_CJ,col_index_initial_CJ] = Jump2DConstraintJacobianInitialSP(iter,NUM_X,NUM_C)
%JUMP2DCONSTRAINTJACOBIANINITIALSP
%    [ROW_INDEX_INITIAL_CJ,COL_INDEX_INITIAL_CJ] = JUMP2DCONSTRAINTJACOBIANINITIALSP(ITER,NUM_X,NUM_C)

%    This function was generated by the Symbolic Math Toolbox version 8.3.
%    27-Aug-2019 12:28:05

t2 = NUM_C.*iter;
t3 = NUM_X.*iter;
t4 = t2+1.0;
t9 = t3+6.0;
t5 = t4+1.0;
t10 = t9+1.0;
t6 = t5+1.0;
t11 = t10+1.0;
t7 = t6+1.0;
t12 = t11+1.0;
t8 = t7+1.0;
row_index_initial_CJ = [t2;t4;t5;t6;t7;t8;t2;t5;t6;t8;t4;t5;t7;t8;t8+1.0;t8+2.0;t2;t5;t6;t8;t4;t5;t7;t8;t8+3.0;t8+4.0];
if nargout > 1
    col_index_initial_CJ = [t3;t3+1.0;t3+2.0;t3+3.0;t3+4.0;t3+5.0;t9;t9;t9;t9;t10;t10;t10;t10;t10;t10;t11;t11;t11;t11;t12;t12;t12;t12;t12;t12];
end
