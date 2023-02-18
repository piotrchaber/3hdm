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
## What are particular and general solutions?
In general, if a solution for a given group and given combination of its representations exists, it can take three forms, namely original, particular or general. Below I will try to briefly define them and give math reasons for their existence, on the example of group [ 36, 3 ] and charged leptons.

**Step 1**: Obtaining original solutions\
First of all, we need to obtain results for considered group, and here are the result we got

<details>
 <summary> Original solutions </summary>
1x1x1<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0.57735,0) (0,0) (0,0) (0,0) (0.57735,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0.57735,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (-0.57735,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.57735,0) (0,0) (0,0) (0,0) (-0.57735,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
1x2x2<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0.288231,0.49923) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.576461,0) (0,0) (0,0) (0,0) (0.288231,0.49923) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0.556085,0) (0,0) (0,0) (0,0) (-0.278043,-0.481584) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0.556085,0) (0,0) (0,0) (0,0) (0,<br/>0) (0,0)]<br/>
1x3x3<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0.288231,-0.49923) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.576461,0) (0,0) (0,0) (0,0) (0.288231,-0.49923) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0.556085,0) (0,0) (0,0) (0,0) (-0.278043,0.481584) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0.556085,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
2x1x2<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.288349,-0.499434) (0,0) (0,0) (0,0) (-0.288349,-0.499434) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0.576697,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0.288675,0.5) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.57735,0) (0,0) (0,0) (0,0) (-0.57735,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
2x2x3<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.170462,-0.295248) (0,0) (0,0) (0,0) (-0.170462,0.295248) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0.340923,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0.278228,-0.481905) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.556456,0) (0,0) (0,0) (0,0) (0.278228,0.481905) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
2x3x1<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (-0.57383,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.57383,0) (0,0) (0,0) (0,0) (0.286915,-0.496951) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.241197,-0.417766) (0,0) (0,0) (0,0) (0.482394,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0.482394,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
3x1x3<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.288349,0.499434) (0,0) (0,0) (0,0) (-0.288349,0.499434) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0.576697,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0.288675,-0.5) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.57735,0) (0,0) (0,0) (0,0) (-0.57735,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
3x2x1<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (-0.57383,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.57383,0) (0,0) (0,0) (0,0) (0.286915,0.496951) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.241197,0.417766) (0,0) (0,0) (0,0) (0.482394,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0.482394,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
3x3x2<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.170462,0.295248) (0,0) (0,0) (0,0) (-0.170462,-0.295248) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0.340923,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0.278228,0.481905) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.556456,0) (0,0) (0,0) (0,0) (0.278228,-0.481905) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]
</details>

These are the regular/raw solutions that have been obtained in the first step. This kind of solutions I call original.

**Step 2**: Obtaining particular solutions\
Scalar multiple of an eigenvector is also an eigenvector for a particular eigenvalue, so we can multiply obtained eigenvectors to the eigenvalue 1 by any scalar. In order to make such a freedom useful it would be best to multiply all obtained eigenvectors in the same way, because this way we are able to eliminate solutions that differ only in the multiplication factor or in other words: length. I decided to multiply eigenvectors in such a way that the first non-zero element is equal to 1.0. This kind of solutions I call particular. Applying the above to our original solutions, we get

<details>
 <summary> Particular solutions </summary>
1x1x1<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
1x2x2<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
1x3x3<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
2x1x2<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
2x2x3<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
2x3x1<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
3x1x3<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
3x2x1<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
3x3x2<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0)]<br/>
[(0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0)]
</details>

**Step 3**: Making the symmetry useful\
In the equation for mass matrix, namely\
<img src="https://latex.codecogs.com/png.image?\dpi{120}&space;M^{l}=-\frac{1}{\sqrt{2}}\Bigg(|v_{1}|h_{1}^{l&space;}+&space;&space;e^{-i\chi_{2}}|v_{2}|h_{2}^{l&space;}+&space;e^{-i\chi_{3}}|v_{3}|h_{3}^{l}\Bigg)" />\
it doesn't matter where the Yukawa matrices will stand, I mean it doesn't matter the order in which the matrices occur (in the end we get the same result no matter if matrix h_1 will be the first, second or third factor of the sum). Yukawa matrices are created from solutions we have obtained, from 27 solution coefficients we get 3 Yukawa matrices - each subsequent 9 coefficients can create one of Yukawa matrices, therefore in the vector solution we can freely swap every next 9-dimensional subvectors with each other. That means solutions that differ only in the order of occurrence of 9-dimensional sub-vectors are exactly the same! So what we need to do? We need to decide how we would like to order the Yukawa matrices/9-dimensional subvectors (one order for all solutions). I decided to sort subvectors by index of its first non-zero element. At the end we can multiply a vector solution by a scalar so that its first non-zero element is equal to 1. After all we have

<details>
 <summary> Pre-general solutions </summary>
1x1x1<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
1x2x2<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0)]<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0)]<br/>
1x3x3<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0)]<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0)]<br/>
2x1x2<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
2x2x3<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0)]<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0)]<br/>
2x3x1<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0)]<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0)]<br/>
3x1x3<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
3x2x1<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0)]<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0)]<br/>
3x3x2<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0) (0,0)]<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,-0.866025) (0,0)]
</details>

**Step 4**: Obtaining general solutions\
From such obtained solutions we can get the general ones. In this case, only the shape/form of the solution is important to us, and to get this shape/form we need to replace all non-zero elements except the first one with the number equal to 1. Now, the first non-zero element is always equal to 1 (so there was no reason to replace it :)), we can call this element the leading coefficient, and all the replaced non-zero elements form a phase of given solution. For example, the second solution for combination 1x2x2, i.e.\
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (-0.5,0.866025) (0,0)]\
has the following general form\
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]\
and phase {(-0.5,0.866025) (-0.5,0.866025)}. While for all solutions we have

<details>
 <summary> General solutions </summary>
1x1x1<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
{(1,0) (1,0)}<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
{(1,0) (1,0)}<br/>
1x2x2<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
{(1,0) (-0.5,0.866025)}<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
{(-0.5,0.866025) (-0.5,0.866025)}<br/>
1x3x3<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
{(1,0) (-0.5,-0.866025)}<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
{(-0.5,-0.866025) (-0.5,-0.866025)}<br/>
2x1x2<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
{(-0.5,0.866025) (1,0)}<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
{(-0.5,-0.866025) (1,0)}<br/>
2x2x3<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
{(-0.5,-0.866025) (-0.5,0.866025)}<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
{(-0.5,-0.866025) (-0.5,0.866025)}<br/>
2x3x1<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
{(-0.5,-0.866025) (-0.5,-0.866025)}<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
{(1,0) (-0.5,-0.866025)}<br/>
3x1x3<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
{(-0.5,-0.866025) (1,0)}<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
{(-0.5,0.866025) (1,0)}<br/>
3x2x1<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
{(-0.5,0.866025) (-0.5,0.866025)}<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
{(1,0) (-0.5,0.866025)}<br/>
3x3x2<br/>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
{(-0.5,0.866025) (-0.5,-0.866025)}<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
{(-0.5,0.866025) (-0.5,-0.866025)}
</details>

**Step 5**: Making the theorem useful\
Any linear combination of eigenvectors in the same eigenspace is another eigenvector in the same eigenspace. So, I have decided to divide any 2- or more-dimensional solutions into 1-dimensional ones (assuming the scalar coefficient for all eigenvectors except one to be equal to zero), and consider them separately. Thus, for the group under consideration, we get 18 one-dimensional solutions.

**Step 6**: Obtaining unique general solutions\
When looking for unique general solutions we take into account both their form and phase. Thus, in the end, for the group [ 36, 3 ], we obtain the following

<details>
 <summary> Unique general solutions </summary>
[(0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0)]<br/>
{(1,0) (1,0)} {(-0.5,0.866025) (-0.5,0.866025)} {(-0.5,-0.866025) (-0.5,-0.866025)} {(-0.5,0.866025) (1,0)} {(-0.5,-0.866025) (-0.5,0.866025)} {(1,0) (-0.5,-0.866025)} {(-0.5,-0.866025) (1,0)} {(1,0) (-0.5,0.866025)} {(-0.5,0.866025) (-0.5,-0.866025)}<br/>
[(0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (0,0) (1,0) (0,0) (0,0)]<br/>
{(1,0) (1,0)} {(1,0) (-0.5,0.866025)} {(1,0) (-0.5,-0.866025)} {(-0.5,-0.866025) (1,0)} {(-0.5,-0.866025) (-0.5,0.866025)} {(-0.5,-0.866025) (-0.5,-0.866025)} {(-0.5,0.866025) (1,0)} {(-0.5,0.866025) (-0.5,0.866025)} {(-0.5,0.866025) (-0.5,-0.866025)}
</details>

18 one-dimensional solutions have been reduced to two unique general forms, each with 9 unique phases.
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
- InvarianceEquationSolver (*represents invariance equation solver, computes particular or general solutions of the invariance equation for a given group*)
- UniqueSolutionsSeeker (*represents unique solutions seeker, finds unique vector-solutions in both particular and general form*)
- MassCalculator (*represents mass calculator, determines mass matrix for a given vector-solution and computes mass ratio of particles*)

## Math definitions
 > **Group** is a set of objects equipped with binary operation acting on these objects and satisfying some mathematical properties called group axiom: the operation is associative, identity element exists, every element has an inverse; example: set of integers {..., -2, -1, 0, 1, 2, ...} with addition as a group operation and 0 as an identity element\
 > **Generators** are group elements from which each element of this group can be obtained by performing finite number of group operation on these elements and their inverses; example: group of integers number is generated by 1, since every integer is a sum of a finite number of +1 and -1\
 > **Matrix representation** of a group is a another description of a group as a group of matrices, in other words: each element of the group is replaced by the matrix in such a way that mathematical properties of the group is preserved\
 > **n-Dimensional representation** is a group of matrices of dimension n-by-n\
 > **Fact:** groups can have many generators as well as many matrix representations, even with the same dimension
