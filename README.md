# 3hdm
## A brief description
From the mathematical point of view, all the physical problem of the 3hdm topic is reduced to solving one of the following three equations (depends on type of particles under consideration):\
<img src="https://latex.codecogs.com/png.image?\dpi{120}&space;N^{l}h^{l}=(A_{\phi}^{\dagger&space;}\otimes&space;&space;A_{L}^{\dagger&space;}\otimes&space;A_{R}^{lT})h^{l}=h^{l}&space;\;\;&space;(charged\_leptons)" title="N^{l}h^{l}=(A_{\phi}^{\dagger }\otimes A_{L}^{\dagger }\otimes A_{R}^{lT})h^{l}=h^{l} \;\; (charged_leptons)" />\
<img src="https://latex.codecogs.com/png.image?\dpi{120}&space;N^{\nu}h^{\nu}=(A_{\phi}^{T}\otimes&space;&space;A_{L}^{\dagger&space;}\otimes&space;A_{R}^{\nu&space;T})h^{\nu}=h^{\nu}&space;\;\;&space;(dirac\_neutrinos)" title="N^{\nu}h^{\nu}=(A_{\phi}^{T}\otimes A_{L}^{\dagger }\otimes A_{R}^{\nu T})h^{\nu}=h^{\nu} \;\; (dirac\_neutrinos)" />\
<img src="https://latex.codecogs.com/png.image?\dpi{120}&space;N^{m}h^{m}=(A_{\phi}^{T}\otimes&space;A_{\phi}^{T}\otimes&space;A_{L}^{\dagger&space;}\otimes&space;A_{L}^{\dagger&space;})h^{m}=h^{m}&space;\;\;&space;(majorana\_neutrinos)" title="N^{m}h^{m}=(A_{\phi}^{T}\otimes A_{\phi}^{T}\otimes A_{L}^{\dagger }\otimes A_{L}^{\dagger })h^{m}=h^{m} \;\; (majorana\_neutrinos)" />\
which have the form of eigenequations to the eigenvalue 1. The above equations I will call invariance equations, and the matrices on the left side, for which we need to solve eigenproblem, I will call invariance matrices accordingly. These matrices are obtained as the result of Kronecker product of matrices of smaller size. So to solve these equations we must have these "small" matrices. Now the question is: where do we get them? And here is the most interesting part of this problem, because they can not be arbitrary, but they must belong to any 3-dimensional matrix representation of mathematical object called group. Matrix representation of a group is just a different description of this group, where a group of n purely abstract elements are replaced by the group of n matrices. For our purposes only the specific elements of the group matter, namely group generators. Thus we have a connection one group generator - one matrix, and because a group may have many 3-dimensional representations, we can extend this connection to one generator - many matrices, where each one belongs to a different representation. There is only one rule for placing matrices into the above equations: they must belong to the same generator (we can not mix matrices of different generators, but we can combine any matrices of one generator). Group may have many generators, so we have to solve the invariance equation for each of them separately. Now notice that if we put a matrices of one generator into invariance equation, they will form a combination of matrix representations of given group. To get the final answer, we need to find a common solution for all group generators, and what is very important within one and the same combination of matrix representations of given group.
## Example
Lets say we have a group that has two 3-dimensional representations denoted by 1 and 2, respectively, and two generators, A and B. Thus each group generator has two matrices, the first one *MA1*, *MA2*, and the second one *MB1*, *MB2*. If we take invariance equation for charged particles into consideration, then the following combinations of matrix representations are possible:\
 { 1x1x1, 1x1x2, 1x2x1, 1x2x2, 2x1x1, 2x1x2, 2x2x1, 2x2x2 }.\
So for the first combination we need to solve two equations, one for each generator\
 *(MA1 x MA1 x MA1)h = h,*\
 *(MB1 x MB1 x MB1)h = h,*\
and then find common solution, for the next combination we have\
 *(MA1 x MA1 x MA2)h = h,*\
 *(MB1 x MB1 x MB2)h = h,*\
and so on for the rest of the cases.
## General plan
All we have are 3-dimensional matrix representations of generators of given group, and from them we need to get something what we can compare with experimental results, namely mass matrices. In a nutshell, the action plan that help us achieve this goal consists the following parts:
 - construct invariance equation matrices for each generator separately
 - solve appropriate invariance equation for each generator separately or in other words: look for the eigenvectors correspond to eigenvalue 1 for invariance equation matrices
 - find common solution, and here is how we can do it: eigenvectors of any square matrix corresponding to the eigenvalue v forms a vector space called the eigenspace, so we need to determine the common eigenspace of the individual eigensubspace and establish the base vector
 - create mass matrices from vector-solutions

That's all we have to do for one group and one combination of matrix representations of this group, so at the end we need to loop above-mentioned steps for all possible combinations and all considered groups.
## From a programming perspective
Now, from programming point of view, we need to introduce functions/methods responsible for:

- loading matrix from file
- establishing the invariant equation
- calculating eigenvectors for eigenvalue equal to 1
- determining intersection basis of many eigensubspaces
- creating mass matrices from vector-solutions
- calculating mass ratio for given mass matrix

and some auxiliary functions/methods responsible for:

- checking if the solution is correct
- finding unique vector-solutions in so-called general form
- finding unique mass matrices

and so on. Based on the above plan I have decided to collect these functions/methods into 7 classes:

- MyMatrix (*represents a normal matrix enriched with a few additional possibilities, in particular may represent a matrix of one group generator*)
- Representation (*represents one 3-dimensional matrix representation of given group, is a collection of matrices of each group generator*)
- Group (*represents one group, is a collection of all 3-dimensional matrix representations of given group*)
- InvarianceEquation (*represents invariance equation solver, computes particular or general solutions of the invariance equation for a given group*)
- Unique (*represents unique solutions seeker, finds unique vector-solutions in both particular and general form*)
- MassMatrix (*represents mass matrix calculator, determines mass matrix for a given vector-solution and computes mass ratio of particles*)

## Math definitions
 > **Group** is a set of objects equipped with binary operation acting on these objects and satisfying some mathematical properties called group axiom: the operation is associative, identity element exists, every element has an inverse; example: set of integers {..., -2, -1, 0, 1, 2, ...} with addition as a group operation and 0 as an identity element\
 > **Generators** are group elements from which each element of this group can be obtained by performing finite number of group operation on these elements and their inverses; example: group of integers number is generated by 1, since every integer is a sum of a finite number of +1 and -1\
 > **Matrix representation** of a group is a another description of a group as a group of matrices, in other words: each element of the group is replaced by the matrix in such a way that mathematical properties of the group is preserved\
 > **n-Dimensional representation** is a group of matrices of dimension n-by-n\
 > **Fact:** groups can have many generators as well as many matrix representations, even with the same dimension
