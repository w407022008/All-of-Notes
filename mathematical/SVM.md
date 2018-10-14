# Kernel Models

|       PLA/pocket       |        linear SVR        |                /                | worse performance |
| ---------------------- | ------------------------ | ------------------------------- | ----------------- |
| linear soft-margin SVM | linear ridge  regression | regularized logistic regression |                   |
| /                      | kernel ridge regession   | kernel logistic regression      | worse performance |
| SVM                    | SVR                      | probabilistic SVM               |                   |

linear Hard-Margin SVM ->non-linear Hard-Margin SVM ->kernel -> soft-margin SVm

## 1、PLA/pocket

## 2、linear SVR

## 3、linear soft-margin SVM

### linear Hard-margin SVM——Primal Hard-Margin SVM
http://www.bilibili.com/video/av9636299/index_2.html

> $max(w): margin(w)$ # w is defined as the line
>> subject-to:every:$ y(n)·w·x(n)>0$
>>> $margin(w)=\min_{n=1}^{N} distance(xn,w)$
>>>
>>>其中： $distance(xn,w)=\frac{|w·x+b|}{|w|}=\frac{y_n(w·x_n+b)}{|w|}$

=>
> $max(b,w): \frac{1}{|w|} <==> min(b,w): \frac{w·w}{2}$
>> subject to: $ y_n·(w·x_n+b) \geq 1 $ for all of n

=>Quadratic Programming
>optimal $u<-Q_p(Q,p,A,c)$
>
>min(u):$u·Q_u/2+p_u$
>
>subject to: $a_n·u \geq c_n$
>>u=[b w]·T

==> $g_{SVM}(x)=sign(w·x+b)$

### non-linear SVM——Dual Hard-Margin SVM
$z_n=phi(x_n)$ to represent the hyperplanes

phi(x) is the feature transform function

> min(b,w): $\frac{W·W}{2}$
>>s.t.: $y_n(w·z_n+b) \geq 1$ for all of n

with Lagrange multipliers $\alpha(n)$

$L(b,w,\alpha(n))= \frac{W·W}{2}+ \sum_n \alpha(1-y_n·(W·z_n+b))$

>SVM；$min_{(b,w)}\{max \{L(b,w,alpha)\} for-all-{\alpha}\} =max_{(\alpha)}[min_{(b,w)}L(b,w,\alpha)]$
>> KKT condition:
>>
>>  1、$\sum (\alpha(n)·y_n)=0$ for all n
>>
>>  2、$w=\sum (\alpha(n)·y_n·z_n)$ for all n
>>
>>  3、$\alpha(n)(1-y_n(w·z_n+b))=0$

> => SVM： $min [\frac{(\sum \alpha(n)·y_n·z_n)^2}{2}-\sum \alpha(n)]$  for all of n

=>
>`standard hard-margin SVM dual`
>>$min_{(\alpha)}:\frac{(\sum\alpha(n)·y_n·z_n)^2}{2}-\sum\alpha(n)$
>>
>>s.t.:
>>$\sum(y_n·\alpha(n))=0$
>>
>>$\alpha \geq 0$ `if $\alpha(s)=\alpha(n)>0$ then the point n is a support vector`

=> QP
=> KKT
=> b=yn-w·zn,w=sum (alpha(n)·yn·zn) for all n

=>
>w=sum (alpha(s)·ys·zs) # s is all of SVpoint
>
b=ys-sum (alpha(s)·ys·zs·zs)
>
gSVM(z)=sign(w·z+b)

### kernel model
zn·zm=K(xn,xm) = kernel model of xn & xm

> kernel model:
>> linear kernel  # degree 1

>> zn·zm = K(xn,xm) = (xn·xm)
>
  .
>> polynomial kernel  # degree Q

>> zn·zm = K(xn,xm) = (theta+gama·xn·xm)^Q  , gama>0, the matrix K must be a semi_definite matrix, Q should be small
>
  .
>> gaussian kernel  #  infinit degree

>> zn·zm = K(xn,xm) = exp(-gama·|xn-xm|^2)  , gama>0

### Kernel Soft-Margin SVM
> object:
>> min(b,w) :
>>
    1/2·w·w+C·sum(keci(n))
    s.t. :
    yn(w·zn+b)>=1-keci(n)
    keci(n)>=0

>=>
>> min(alpha) :
>>
    1/2·w·w-sum(alpha(n))
    s.t. :
    sum(yn·alpha(n))=0
    0<=alpha(n)<=C

the same method(kernel QP) to solve alpha(n)
> KKT condition
>>
    1、sum (alpha(n)·yn)=0 for all n
    2、w=sum (alpha(n)·yn·zn) for all n
    3、alpha(n)(1-keci(n)-yn(w·zn+b))=0
>>
    0<alpha(n)<C:
    ·alpha(n)=0 : keci = 0 : correctly
    ·0<alpha(n)<C : keci=0 : the point is on the boundary
    ·alpha(n)=C : keci = yn-(w·zn+b): the error of the point is the keci
    ·the more C, the more probability of overfit

=> b= ys-sum( alpha(n) · yn · K(xn,xs) )

w=

gSVm=

## 4、linear ridge regression

## 5、regularized logistic regression
is approximate as SVM

## 6、kernel ridge regression=least-squares SVM(LSSVM)
> object:
>> min(b,w) :
>>
lambda/N·W·W+1/N·sum[(yn-W·zn)^2]

> optimal solution : W*=sum[beta(n)·zn]

> can solve for optimal beta instead of W

=>
>>min(beta) :

>> lambda/N·beta·K·beta+1/N·|y-K·beta|^2

> beta=inv(lambda·I+K)·y , always exists for lambda>0

> time complexity:O(N^3),it's heavy to solve because of K is big

## 7、kernel logistic regression
> object:
>> min(b,w) :
>>
lambda/N·W·W+1/N·sum[log2(1+exp(-yn·w·zn))]

> optimal solution : W*=sum[beta(n)·zn]

> can solve for optimal beta instead of W

=>
>>min(beta) :

>> lambda/N·beta·K·beta+1/N·sum(log2(1+exp(-yn·sum(beta·K))))

> almost beta is not 0, it's not very good

## 8、SVM

## 9、SVR——support vector regression
### L2-Regularized Tube Regression
> object:
>> min(b,w) :
>>
    lambda/N·W·W+1/N·sum[max(0,|w·zn-y|-e)]
>>
<==>
>>
    1/2·w·+C·sum[max(0,|w·zn+b-yn|-e)]
    s.t.: -e-keci(n)1<=yn-w·zn-b<=e+keci(n)2

>=>
>> min(alpha1,alpha2)
>>
    1/2·w·w+sum[(e-yn)·alpha2+(e+yn)·alpha1]
    s.t.:
    sum[alpha2-alpha1]=0
    0<=alpha2<=C
    0<=alpha1<=C

> KKT condition
>>
    1、w=sum(alpha2-alpha1)·zn
    2、0=sum(alpha2-alpha1)
    3、alpha2·(e+keci(n)2-yn+w·zn+b)=0
    4、alpha1·(e+keci(n)1-yn+w·zn+b)=0

> 1、strictly within tube |w·zn+b-yn|<e

>beta(n)=alpha2-alpha1=0

> 2、beta(n)!=0 : on or outside Tube

## 10、probabilistic SVM for soft binary classification
>
    1、run SVM on D to get (bSVM,wSVM)[or the duel alpha],and transform D to zn=wSVM·phi(xn)+bSVM
    2、run logistic regression on {(zn,yn)}1..N to get (A,B)
    3、return g(x)=theta(A·(wSVM·phi(x)+bSVm)+B)
