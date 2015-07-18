/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_LIBS_ICL_TEST_ICL_LAWS_HPP_JOFA_090119
#define BOOST_LIBS_ICL_TEST_ICL_LAWS_HPP_JOFA_090119

#include <functional>
#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/associative_interval_container.hpp>

namespace boost{namespace icl
{

template<class Type>
struct equality : std::binary_function<Type,Type,bool> 
{
    typedef bool (type)(const Type&, const Type&);
};

//------------------------------------------------------------------------------
// Associativity
//------------------------------------------------------------------------------

// The definition of a boost test via a macro, that allows to be instantiated for
// different operator signs 'op_sign'. For every 'op_sign' a separate function
// template is generated by appending the suffic 'op_tag' to the function 
// name.
// So this is the function template via macro that checks the law 
// associativity for an operator 'op_sign'
#define DEFINE_ASSOCIATIVITY_CHECK_WRT(op_tag, op_sign) \
template<class Type, class TypeB, class TypeC> \
void check_associativity_wrt_##op_tag(const Type& a, const TypeB& b, const TypeC& c) \
{ \
    Type left  = (a op_sign b) op_sign c; \
    Type right = a op_sign (b op_sign c); \
    BOOST_CHECK(left==right); \
}

#define DEFINE_ASSOCIATIVITY_CHECK_WRT_EQUAL(op_tag, op_sign) \
template<class Type, class TypeB, class TypeC> \
void check_associativity_wrt_equal_##op_tag \
(typename equality<Type>::type* equal, \
const Type& a, const TypeB& b, const TypeC& c) \
{ \
    Type left  = (a op_sign b) op_sign c; \
    Type right = a op_sign (b op_sign c); \
    BOOST_CHECK((*equal)(left,right)); \
}

// Here we define the call of the test function thats definition 
// template has been generated by the macro above.
#define CHECK_ASSOCIATIVITY_WRT(op_tag)       check_associativity_wrt_##op_tag
#define CHECK_ASSOCIATIVITY_WRT_EQUAL(op_tag) check_associativity_wrt_equal_##op_tag

// Here we actually generate function templates by calling the defining
// macros.
DEFINE_ASSOCIATIVITY_CHECK_WRT      (plus,  + )
DEFINE_ASSOCIATIVITY_CHECK_WRT_EQUAL(plus,  + )
DEFINE_ASSOCIATIVITY_CHECK_WRT      (pipe,  | )
DEFINE_ASSOCIATIVITY_CHECK_WRT_EQUAL(pipe,  | )
DEFINE_ASSOCIATIVITY_CHECK_WRT      (et,    & )
DEFINE_ASSOCIATIVITY_CHECK_WRT_EQUAL(et,    & )
DEFINE_ASSOCIATIVITY_CHECK_WRT      (caret, ^ )
DEFINE_ASSOCIATIVITY_CHECK_WRT_EQUAL(caret, ^ )


//------------------------------------------------------------------------------
// Neutrality
//------------------------------------------------------------------------------

#define DEFINE_RIGHT_NEUTRALITY_CHECK_WRT_EQUAL(op_tag, op_sign) \
template<class Type> \
void check_right_neutrality_wrt_equal_##op_tag \
(typename equality<Type>::type* equal, const Type& a, const Type& identity_element) \
{ \
    Type left  = a op_sign identity_element; \
    Type right = identity_element; \
    BOOST_CHECK((*equal)(left,right)); \
}

#define DEFINE_RIGHT_NEUTRALITY_CHECK_WRT(op_tag, op_sign) \
template<class Type> \
void check_right_neutrality_wrt_##op_tag \
(typename equality<Type>::type* equal, const Type& a, const Type& identity_element) \
{ \
    Type left  = a op_sign identity_element; \
    Type right = identity_element; \
    BOOST_CHECK(left==right); \
}

#define DEFINE_NEUTRALITY_CHECK_WRT_EQUAL(op_tag, op_sign) \
template<class Type> \
void check_neutrality_wrt_equal_##op_tag \
(typename equality<Type>::type* equal, const Type& a, const Type& identity_element) \
{ \
    Type left  = a op_sign identity_element; \
    Type right = identity_element op_sign a; \
    BOOST_CHECK((*equal)(left,right)); \
}

#define DEFINE_NEUTRALITY_CHECK_WRT(op_tag, op_sign) \
template<class Type> \
void check_neutrality_wrt_##op_tag \
(const Type& a, const Type& identity_element) \
{ \
    Type left  = a op_sign identity_element; \
    Type right = identity_element op_sign a; \
    BOOST_CHECK(left==right); \
}

#define CHECK_NEUTRALITY_WRT(op_tag) check_neutrality_wrt_##op_tag
#define CHECK_NEUTRALITY_WRT_EQUAL(op_tag) check_neutrality_wrt_equal_##op_tag

DEFINE_NEUTRALITY_CHECK_WRT      (plus,  + )
DEFINE_NEUTRALITY_CHECK_WRT_EQUAL(plus,  + )
DEFINE_NEUTRALITY_CHECK_WRT      (pipe,  | )
DEFINE_NEUTRALITY_CHECK_WRT_EQUAL(pipe,  | )
DEFINE_NEUTRALITY_CHECK_WRT      (minus, - )
DEFINE_NEUTRALITY_CHECK_WRT_EQUAL(minus, - )
DEFINE_NEUTRALITY_CHECK_WRT      (et,    & )
DEFINE_NEUTRALITY_CHECK_WRT_EQUAL(et,    & )
DEFINE_NEUTRALITY_CHECK_WRT      (caret, ^ )
DEFINE_NEUTRALITY_CHECK_WRT_EQUAL(caret, ^ )

//------------------------------------------------------------------------------
// Commutativity
//------------------------------------------------------------------------------

#define DEFINE_COMMUTATIVITY_CHECK_WRT_EQUAL(op_tag, op_sign) \
template<class Type, class TypeB> \
void check_commutativity_wrt_equal_##op_tag \
(typename equality<Type>::type* equal, const Type& a, const TypeB& b) \
{ \
    Type left  = a op_sign b; \
    Type right = b op_sign a; \
    BOOST_CHECK((*equal)(left,right)); \
}

#define DEFINE_COMMUTATIVITY_CHECK_WRT(op_tag, op_sign) \
template<class Type, class TypeB> \
    void check_commutativity_wrt_##op_tag(const Type& a, const TypeB& b) \
{ \
    Type left  = a op_sign b; \
    Type right = b op_sign a; \
    BOOST_CHECK(left==right); \
}

#define CHECK_COMMUTATIVITY_WRT_EQUAL(op_tag) check_commutativity_wrt_equal_##op_tag
#define CHECK_COMMUTATIVITY_WRT(op_tag) check_commutativity_wrt_##op_tag

DEFINE_COMMUTATIVITY_CHECK_WRT      (plus,  + )
DEFINE_COMMUTATIVITY_CHECK_WRT_EQUAL(plus,  + )
DEFINE_COMMUTATIVITY_CHECK_WRT      (pipe,  | )
DEFINE_COMMUTATIVITY_CHECK_WRT_EQUAL(pipe,  | )
DEFINE_COMMUTATIVITY_CHECK_WRT      (et,    & )
DEFINE_COMMUTATIVITY_CHECK_WRT_EQUAL(et,    & )
DEFINE_COMMUTATIVITY_CHECK_WRT      (caret, ^ )
DEFINE_COMMUTATIVITY_CHECK_WRT_EQUAL(caret, ^ )

//------------------------------------------------------------------------------
// Natural inversion
//------------------------------------------------------------------------------

#define DEFINE_PARTIAL_INVERSION_CHECK_WRT_EQUAL(plus_tag, plus_sign) \
template<class Type> \
    void check_partial_inversion_wrt_equal_##plus_tag \
(typename equality<Type>::type* equal, const Type& identity_element, const Type& var_a) \
{ \
    Type positive_difference  = var_a - var_a; \
    BOOST_CHECK((*equal)(positive_difference, identity_element)); \
}

#define DEFINE_PARTIAL_INVERSION_CHECK_WRT(plus_tag, plus_sign) \
template<class Type> \
    void check_partial_inversion_wrt_##plus_tag \
(const Type& identity_element, const Type& var_a) \
{ \
    Type positive_difference  = var_a - var_a; \
    BOOST_CHECK(positive_difference==identity_element); \
}

#define CHECK_PARTIAL_INVERSION_WRT_EQUAL(plus_tag) check_partial_inversion_wrt_equal_##plus_tag
#define CHECK_PARTIAL_INVERSION_WRT(plus_tag) check_partial_inversion_wrt_##plus_tag

DEFINE_PARTIAL_INVERSION_CHECK_WRT      (plus,  + )
DEFINE_PARTIAL_INVERSION_CHECK_WRT_EQUAL(plus,  + )
DEFINE_PARTIAL_INVERSION_CHECK_WRT      (pipe,  | )
DEFINE_PARTIAL_INVERSION_CHECK_WRT_EQUAL(pipe,  | )

//------------------------------------------------------------------------------
// Inverse
//------------------------------------------------------------------------------

#define DEFINE_INVERSE_CHECK_WRT_EQUAL(plus_tag, plus_sign) \
template<class Type> \
    void check_inverse_wrt_equal_##plus_tag \
(typename equality<Type>::type* equal, const Type& identity_element, const Type& var_a) \
{ \
    Type positive_difference  = var_a - var_a; \
    BOOST_CHECK((*equal)(positive_difference, identity_element)); \
    Type negative_difference = (identity_element - var_a) plus_sign var_a; \
    BOOST_CHECK((*equal)(negative_difference, identity_element)); \
}

#define DEFINE_INVERSE_CHECK_WRT(plus_tag, plus_sign) \
template<class Type> \
    void check_inverse_wrt_##plus_tag \
(const Type& identity_element, const Type& var_a) \
{ \
    Type positive_difference  = var_a - var_a; \
    BOOST_CHECK(positive_difference==identity_element); \
    Type negative_difference = (identity_element - var_a) plus_sign var_a; \
    BOOST_CHECK(negative_difference==identity_element); \
}

#define CHECK_INVERSE_WRT_EQUAL(plus_tag) check_inverse_wrt_equal_##plus_tag
#define CHECK_INVERSE_WRT(plus_tag) check_inverse_wrt_##plus_tag

DEFINE_INVERSE_CHECK_WRT      (plus,  + )
DEFINE_INVERSE_CHECK_WRT_EQUAL(plus,  + )
DEFINE_INVERSE_CHECK_WRT      (pipe,  | )
DEFINE_INVERSE_CHECK_WRT_EQUAL(pipe,  | )

//------------------------------------------------------------------------------
// Containedness laws (Valid for sets, NOT for maps)
//------------------------------------------------------------------------------
template<class Type, class TypeB>
void check_intersection_containedness(const Type& a, const TypeB& b)
{
    BOOST_CHECK_EQUAL(contains(a, a & b), true);
    BOOST_CHECK_EQUAL(contains(a, b & a), true);
    BOOST_CHECK_EQUAL(within(a & b, a), true);
    BOOST_CHECK_EQUAL(within(b & a, a), true);
}

template<class Type, class TypeB>
void check_union_containedness(const Type& a, const TypeB& b)
{
    BOOST_CHECK_EQUAL(within(a, a + b), true);
    BOOST_CHECK_EQUAL(within(a, b + a), true);
    BOOST_CHECK_EQUAL(contains(a + b, a), true);
    BOOST_CHECK_EQUAL(contains(b + a, a), true);
}

template<class MapT>
void check_domain_containedness(const MapT& a)
{
    typedef typename MapT::set_type set_type;
    set_type dom;
    domain(dom, a);
    BOOST_CHECK_EQUAL(within(dom, a), true);
    BOOST_CHECK_EQUAL(contains(a, dom), true);

    if(!dom.empty())
    {
        typename MapT::domain_type a1 = *dom.begin();
        BOOST_CHECK_EQUAL(within(a1, a), true);
        BOOST_CHECK_EQUAL(contains(a, a1), true);
    }
}

//------------------------------------------------------------------------------
// Laws on inner complement, between and distance
//------------------------------------------------------------------------------
template<class Type, class SetT>
bool check_length_as_distance( const Type& object
                             , SetT& in_between
                             , typename Type::difference_type& between_len
                             , typename Type::difference_type& obj_dist )
{
    //LAW LengthAsDistance: distance(x) == length(between(x))
    icl::between(in_between, object);
    between_len  = icl::length(in_between);
    obj_dist     = icl::distance(object);
    BOOST_CHECK_EQUAL(obj_dist, between_len);
    return obj_dist == between_len;
}

template<class Type, class SetT>
bool has_length_as_distance(const Type& object)
{
    typedef typename Type::difference_type DiffT;
    SetT in_between; DiffT between_len, obj_dist;
    return check_length_as_distance(object, in_between, between_len, obj_dist);
}

template<class Type>
bool check_length_complementarity( const Type& object
                                 , typename Type::difference_type& obj_len
                                 , typename Type::difference_type& obj_dist
                                 , typename Type::difference_type& hull_len )
{
    //LAW Length Complementarity: length(x) + distance(x) == length(hull(x))
    obj_len  = icl::length(object);
    obj_dist = icl::distance(object);
    hull_len = icl::length(hull(object));
    BOOST_CHECK_EQUAL(obj_len + obj_dist, hull_len);
    return obj_len + obj_dist == hull_len;
}

template<class Type>
bool has_length_complementarity(const Type& object)
{
    typedef typename Type::difference_type DiffT;
    DiffT obj_len, obj_dist, hull_len;
    return check_length_complementarity(object, obj_len, obj_dist, hull_len);
}

template<class Type, class SetT>
bool check_inner_complementarity(const Type& object, SetT& in_between, SetT& lhs, SetT& rhs)
{
    //LAW Inner Complementarity1: domain(x) + between(x)       =e= hull(x)
    //LAW Inner Complementarity2: join(domain(x) + between(x))  == hull(x)
    SetT dom;
    icl::domain(dom, object);
    lhs = dom + between(in_between, object);
    join(lhs);
    rhs = SetT(hull(object));
    BOOST_CHECK_EQUAL(lhs, rhs);
    return lhs == rhs;
}


template<class Type, class SetT>
bool has_inner_complementarity(const Type& object)
{
    SetT in_between, lhs, rhs;
    return check_inner_complementarity(object, in_between, lhs, rhs);
}



//==============================================================================
// Law tests are now combined to test algebraic concepts.
//------------------------------------------------------------------------------
// Monodid EAN
//------------------------------------------------------------------------------

#define DEFINE_MONOID_CHECK_WRT_EQUAL(op_tag) \
template<class Type, class TypeB, class TypeC> \
void check_monoid_wrt_equal_##op_tag \
(typename equality<Type>::type* equal, const Type& identity_element, \
const Type& a, const TypeB& b, const TypeC& c) \
{ \
    CHECK_ASSOCIATIVITY_WRT_EQUAL(op_tag)(equal,a,b,c); \
    CHECK_NEUTRALITY_WRT_EQUAL(op_tag)(equal,a,identity_element); \
}

#define DEFINE_MONOID_CHECK_WRT(op_tag) \
template<class Type, class TypeB, class TypeC> \
void check_monoid_wrt_##op_tag \
(const Type& identity_element, \
const Type& a, const TypeB& b, const TypeC& c) \
{ \
    CHECK_ASSOCIATIVITY_WRT(op_tag)(a,b,c); \
    CHECK_NEUTRALITY_WRT(op_tag)(a,identity_element); \
}

DEFINE_MONOID_CHECK_WRT      (plus)
DEFINE_MONOID_CHECK_WRT_EQUAL(plus)
DEFINE_MONOID_CHECK_WRT      (pipe)
DEFINE_MONOID_CHECK_WRT_EQUAL(pipe)
DEFINE_MONOID_CHECK_WRT      (et)
DEFINE_MONOID_CHECK_WRT_EQUAL(et)
DEFINE_MONOID_CHECK_WRT      (caret)
DEFINE_MONOID_CHECK_WRT_EQUAL(caret)

#define CHECK_MONOID_WRT(op_tag) check_monoid_wrt_##op_tag
#define CHECK_MONOID_WRT_EQUAL(op_tag) check_monoid_wrt_equal_##op_tag

//------------------------------------------------------------------------------
// Commutative or Abelian monodid EANC
//------------------------------------------------------------------------------
#define DEFINE_ABELIAN_MONOID_CHECK_WRT_EQUAL(op_tag) \
template<class Type, class TypeB, class TypeC> \
void check_abelian_monoid_wrt_equal_##op_tag \
(typename equality<Type>::type* equal, const Type& identity_element, \
const Type& a, const TypeB& b, const TypeC& c) \
{ \
    CHECK_ASSOCIATIVITY_WRT_EQUAL(op_tag)(equal,a,b,c); \
    CHECK_NEUTRALITY_WRT_EQUAL(op_tag)(equal,a,identity_element); \
    CHECK_COMMUTATIVITY_WRT_EQUAL(op_tag)(equal,a,b); \
    CHECK_COMMUTATIVITY_WRT_EQUAL(op_tag)(equal,a,c); \
}

#define DEFINE_ABELIAN_MONOID_CHECK_WRT(op_tag) \
template<class Type, class TypeB, class TypeC> \
void check_abelian_monoid_wrt_##op_tag \
(const Type& identity_element, \
const Type& a, const TypeB& b, const TypeC& c) \
{ \
    CHECK_ASSOCIATIVITY_WRT(op_tag)(a,b,c); \
    CHECK_NEUTRALITY_WRT(op_tag)(a,identity_element); \
    CHECK_COMMUTATIVITY_WRT(op_tag)(a,b); \
    CHECK_COMMUTATIVITY_WRT(op_tag)(a,c); \
}

DEFINE_ABELIAN_MONOID_CHECK_WRT      (plus)
DEFINE_ABELIAN_MONOID_CHECK_WRT_EQUAL(plus)
DEFINE_ABELIAN_MONOID_CHECK_WRT      (pipe)
DEFINE_ABELIAN_MONOID_CHECK_WRT_EQUAL(pipe)
DEFINE_ABELIAN_MONOID_CHECK_WRT      (et)
DEFINE_ABELIAN_MONOID_CHECK_WRT_EQUAL(et)
DEFINE_ABELIAN_MONOID_CHECK_WRT      (caret)
DEFINE_ABELIAN_MONOID_CHECK_WRT_EQUAL(caret)

#define CHECK_ABELIAN_MONOID_WRT(op_tag) check_abelian_monoid_wrt_##op_tag
#define CHECK_ABELIAN_MONOID_WRT_EQUAL(op_tag) check_abelian_monoid_wrt_equal_##op_tag

//------------------------------------------------------------------------------
// Abelian monodid EANC with partial inversion
//------------------------------------------------------------------------------
#define DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_WRT_EQUAL(op_tag) \
template<class Type, class TypeB, class TypeC> \
void check_partial_invertive_monoid_wrt_equal_##op_tag \
(typename equality<Type>::type* equal, const Type& identity_element, \
const Type& a, const TypeB& b, const TypeC& c) \
{ \
    CHECK_ABELIAN_MONOID_WRT_EQUAL(op_tag)(equal,identity_element,a,b,c); \
    CHECK_PARTIAL_INVERSION_WRT_EQUAL(op_tag)(equal,identity_element,a); \
}

#define DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_WRT(op_tag) \
template<class Type, class TypeB, class TypeC> \
void check_partial_invertive_monoid_wrt_##op_tag \
(const Type& identity_element, \
const Type& a, const TypeB& b, const TypeC& c) \
{ \
    CHECK_ABELIAN_MONOID_WRT(op_tag)(identity_element,a,b,c); \
    CHECK_PARTIAL_INVERSION_WRT(op_tag)(identity_element,a); \
}

DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_WRT      (plus)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_WRT_EQUAL(plus)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_WRT      (pipe)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_WRT_EQUAL(pipe)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_WRT      (et)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_WRT_EQUAL(et)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_WRT      (caret)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_WRT_EQUAL(caret)

#define CHECK_PARTIAL_INVERTIVE_MONOID_WRT(op_tag) check_partial_invertive_monoid_wrt_##op_tag
#define CHECK_PARTIAL_INVERTIVE_MONOID_WRT_EQUAL(op_tag) check_partial_invertive_monoid_wrt_equal_##op_tag

//------------------------------------------------------------------------------
// Abelian group EANIC
//------------------------------------------------------------------------------

#define DEFINE_ABELIAN_GROUP_CHECK_WRT_EQUAL(op_tag) \
template<class Type, class TypeB, class TypeC> \
    void check_abelian_group_wrt_equal_##op_tag \
(typename equality<Type>::type* equal, const Type& identity_element, \
const Type& a, const TypeB& b, const TypeC& c) \
{ \
    CHECK_ABELIAN_MONOID_WRT_EQUAL(op_tag)(equal,identity_element,a,b,c); \
    CHECK_INVERSE_WRT_EQUAL(op_tag)(equal,identity_element,a); \
}

#define DEFINE_ABELIAN_GROUP_CHECK_WRT(op_tag) \
template<class Type, class TypeB, class TypeC> \
    void check_abelian_group_wrt_##op_tag \
(const Type& identity_element, \
const Type& a, const TypeB& b, const TypeC& c) \
{ \
    CHECK_ABELIAN_MONOID_WRT(op_tag)(identity_element,a,b,c); \
    CHECK_INVERSE_WRT(op_tag)(identity_element,a); \
}


DEFINE_ABELIAN_GROUP_CHECK_WRT      (plus)
DEFINE_ABELIAN_GROUP_CHECK_WRT_EQUAL(plus)
DEFINE_ABELIAN_GROUP_CHECK_WRT      (pipe)
DEFINE_ABELIAN_GROUP_CHECK_WRT_EQUAL(pipe)

#define CHECK_ABELIAN_GROUP_WRT(op_tag) check_abelian_group_wrt_##op_tag
#define CHECK_ABELIAN_GROUP_WRT_EQUAL(op_tag) check_abelian_group_wrt_equal_##op_tag

//------------------------------------------------------------------------------
// Modoid permuted
//------------------------------------------------------------------------------

#define DEFINE_MONOID_CHECK_PERMUTED_WRT_EQUAL(op_tag) \
template<class TypeA, class TypeB, class Assoc> \
void check_monoid_permuted_wrt_equal_##op_tag \
(typename equality<TypeA>::type* equal, const TypeA& var_a, const TypeB& var_b, const Assoc& assoc) \
{ \
    CHECK_MONOID_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeA>::value(), var_a, var_b, assoc);\
    CHECK_MONOID_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeA>::value(), var_a, assoc, var_b);\
    CHECK_MONOID_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeB>::value(), var_b, var_a, assoc);\
    CHECK_MONOID_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeB>::value(), var_b, assoc, var_a);\
}

#define DEFINE_MONOID_CHECK_PERMUTED_WRT(op_tag) \
template<class TypeA, class TypeB, class Assoc> \
void check_monoid_permuted_wrt_##op_tag \
(const TypeA& var_a, const TypeB& var_b, const Assoc& assoc) \
{ \
    CHECK_MONOID_WRT(op_tag)(icl::identity_element<TypeA>::value(), var_a, var_b, assoc);\
    CHECK_MONOID_WRT(op_tag)(icl::identity_element<TypeA>::value(), var_a, assoc, var_b);\
    CHECK_MONOID_WRT(op_tag)(icl::identity_element<TypeB>::value(), var_b, var_a, assoc);\
    CHECK_MONOID_WRT(op_tag)(icl::identity_element<TypeB>::value(), var_b, assoc, var_a);\
}


DEFINE_MONOID_CHECK_PERMUTED_WRT      (plus)
DEFINE_MONOID_CHECK_PERMUTED_WRT_EQUAL(plus)
DEFINE_MONOID_CHECK_PERMUTED_WRT      (pipe)
DEFINE_MONOID_CHECK_PERMUTED_WRT_EQUAL(pipe)
DEFINE_MONOID_CHECK_PERMUTED_WRT      (et)
DEFINE_MONOID_CHECK_PERMUTED_WRT_EQUAL(et)
DEFINE_MONOID_CHECK_PERMUTED_WRT      (caret)
DEFINE_MONOID_CHECK_PERMUTED_WRT_EQUAL(caret)

#define CHECK_MONOID_PERMUTED_WRT(op_tag)       check_monoid_permuted_wrt_##op_tag
#define CHECK_MONOID_PERMUTED_WRT_EQUAL(op_tag) check_monoid_permuted_wrt_equal_##op_tag


//------------------------------------------------------------------------------
// Abelian modoid permuted
//------------------------------------------------------------------------------

#define DEFINE_ABELIAN_MONOID_CHECK_PERMUTED_WRT_EQUAL(op_tag) \
template<class TypeA, class TypeB, class Assoc> \
void check_abelian_monoid_permuted_wrt_equal_##op_tag \
(typename equality<TypeA>::type* equal, const TypeA& var_a, const TypeB& var_b, const Assoc& assoc) \
{ \
    CHECK_ABELIAN_MONOID_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeA>::value(), var_a, var_b, assoc);\
    CHECK_ABELIAN_MONOID_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeA>::value(), var_a, assoc, var_b);\
    CHECK_ABELIAN_MONOID_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeB>::value(), var_b, var_a, assoc);\
    CHECK_ABELIAN_MONOID_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeB>::value(), var_b, assoc, var_a);\
}

#define DEFINE_ABELIAN_MONOID_CHECK_PERMUTED_WRT(op_tag) \
template<class TypeA, class TypeB, class Assoc> \
void check_abelian_monoid_permuted_wrt_##op_tag \
(const TypeA& var_a, const TypeB& var_b, const Assoc& assoc) \
{ \
    CHECK_ABELIAN_MONOID_WRT(op_tag)(icl::identity_element<TypeA>::value(), var_a, var_b, assoc);\
    CHECK_ABELIAN_MONOID_WRT(op_tag)(icl::identity_element<TypeA>::value(), var_a, assoc, var_b);\
    CHECK_ABELIAN_MONOID_WRT(op_tag)(icl::identity_element<TypeB>::value(), var_b, var_a, assoc);\
    CHECK_ABELIAN_MONOID_WRT(op_tag)(icl::identity_element<TypeB>::value(), var_b, assoc, var_a);\
}


DEFINE_ABELIAN_MONOID_CHECK_PERMUTED_WRT      (plus)
DEFINE_ABELIAN_MONOID_CHECK_PERMUTED_WRT_EQUAL(plus)
DEFINE_ABELIAN_MONOID_CHECK_PERMUTED_WRT      (pipe)
DEFINE_ABELIAN_MONOID_CHECK_PERMUTED_WRT_EQUAL(pipe)
DEFINE_ABELIAN_MONOID_CHECK_PERMUTED_WRT      (et)
DEFINE_ABELIAN_MONOID_CHECK_PERMUTED_WRT_EQUAL(et)
DEFINE_ABELIAN_MONOID_CHECK_PERMUTED_WRT      (caret)
DEFINE_ABELIAN_MONOID_CHECK_PERMUTED_WRT_EQUAL(caret)

#define CHECK_ABELIAN_MONOID_PERMUTED_WRT(op_tag)       check_abelian_monoid_permuted_wrt_##op_tag
#define CHECK_ABELIAN_MONOID_PERMUTED_WRT_EQUAL(op_tag) check_abelian_monoid_permuted_wrt_equal_##op_tag


//------------------------------------------------------------------------------
// Abelian modoid with partial inversion permuted
//------------------------------------------------------------------------------

#define DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_PERMUTED_WRT_EQUAL(op_tag) \
template<class TypeA, class TypeB, class Assoc> \
void check_partial_invertive_monoid_permuted_wrt_equal_##op_tag \
(typename equality<TypeA>::type* equal, const TypeA& var_a, const TypeB& var_b, const Assoc& assoc) \
{ \
    CHECK_PARTIAL_INVERTIVE_MONOID_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeA>::value(), var_a, var_b, assoc);\
    CHECK_PARTIAL_INVERTIVE_MONOID_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeA>::value(), var_a, assoc, var_b);\
    CHECK_PARTIAL_INVERTIVE_MONOID_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeB>::value(), var_b, var_a, assoc);\
    CHECK_PARTIAL_INVERTIVE_MONOID_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeB>::value(), var_b, assoc, var_a);\
}

#define DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_PERMUTED_WRT(op_tag) \
template<class TypeA, class TypeB, class Assoc> \
void check_partial_invertive_monoid_permuted_wrt_##op_tag \
(const TypeA& var_a, const TypeB& var_b, const Assoc& assoc) \
{ \
    CHECK_PARTIAL_INVERTIVE_MONOID_WRT(op_tag)(icl::identity_element<TypeA>::value(), var_a, var_b, assoc);\
    CHECK_PARTIAL_INVERTIVE_MONOID_WRT(op_tag)(icl::identity_element<TypeA>::value(), var_a, assoc, var_b);\
    CHECK_PARTIAL_INVERTIVE_MONOID_WRT(op_tag)(icl::identity_element<TypeB>::value(), var_b, var_a, assoc);\
    CHECK_PARTIAL_INVERTIVE_MONOID_WRT(op_tag)(icl::identity_element<TypeB>::value(), var_b, assoc, var_a);\
}


DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_PERMUTED_WRT      (plus)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_PERMUTED_WRT_EQUAL(plus)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_PERMUTED_WRT      (pipe)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_PERMUTED_WRT_EQUAL(pipe)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_PERMUTED_WRT      (et)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_PERMUTED_WRT_EQUAL(et)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_PERMUTED_WRT      (caret)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_PERMUTED_WRT_EQUAL(caret)

#define CHECK_PARTIAL_INVERTIVE_MONOID_PERMUTED_WRT(op_tag)       check_partial_invertive_monoid_permuted_wrt_##op_tag
#define CHECK_PARTIAL_INVERTIVE_MONOID_PERMUTED_WRT_EQUAL(op_tag) check_partial_invertive_monoid_permuted_wrt_equal_##op_tag


//------------------------------------------------------------------------------
// Abelian group permuted
//------------------------------------------------------------------------------

#define DEFINE_ABELIAN_GROUP_CHECK_PERMUTED_WRT_EQUAL(op_tag) \
template<class TypeA, class TypeB, class Assoc> \
    void check_abelian_group_permuted_wrt_equal_##op_tag \
(typename equality<TypeA>::type* equal, const TypeA& var_a, const TypeB& var_b, const Assoc& assoc) \
{ \
    CHECK_ABELIAN_GROUP_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeA>::value(), var_a, var_b, assoc);\
    CHECK_ABELIAN_GROUP_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeA>::value(), var_a, assoc, var_b);\
    CHECK_ABELIAN_GROUP_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeB>::value(), var_b, var_a, assoc);\
    CHECK_ABELIAN_GROUP_WRT_EQUAL(op_tag)(equal, icl::identity_element<TypeB>::value(), var_b, assoc, var_a);\
}

#define DEFINE_ABELIAN_GROUP_CHECK_PERMUTED_WRT(op_tag) \
template<class TypeA, class TypeB, class Assoc> \
    void check_abelian_group_permuted_wrt_##op_tag \
(const TypeA& var_a, const TypeB& var_b, const Assoc& assoc) \
{ \
    CHECK_ABELIAN_GROUP_WRT(op_tag)(icl::identity_element<TypeA>::value(), var_a, var_b, assoc);\
    CHECK_ABELIAN_GROUP_WRT(op_tag)(icl::identity_element<TypeA>::value(), var_a, assoc, var_b);\
    CHECK_ABELIAN_GROUP_WRT(op_tag)(icl::identity_element<TypeB>::value(), var_b, var_a, assoc);\
    CHECK_ABELIAN_GROUP_WRT(op_tag)(icl::identity_element<TypeB>::value(), var_b, assoc, var_a);\
}


DEFINE_ABELIAN_GROUP_CHECK_PERMUTED_WRT      (plus)
DEFINE_ABELIAN_GROUP_CHECK_PERMUTED_WRT_EQUAL(plus)
DEFINE_ABELIAN_GROUP_CHECK_PERMUTED_WRT      (pipe)
DEFINE_ABELIAN_GROUP_CHECK_PERMUTED_WRT_EQUAL(pipe)

#define CHECK_ABELIAN_GROUP_PERMUTED_WRT(op_tag)       check_abelian_group_permuted_wrt_##op_tag
#define CHECK_ABELIAN_GROUP_PERMUTED_WRT_EQUAL(op_tag) check_abelian_group_permuted_wrt_equal_##op_tag


//------------------------------------------------------------------------------
// Modoid instance
//------------------------------------------------------------------------------

#define DEFINE_MONOID_CHECK_INSTANCE_WRT_EQUAL(op_tag) \
template<class TypeA, class TypeB, class TypeC, class AssocA, class AssocB> \
void check_monoid_instance_wrt_equal_##op_tag \
(typename equality<TypeA>::type* equal, const TypeA& var_a, const TypeB& var_b, const TypeC& var_c, \
 const AssocA& ass_a, const AssocB& ass_b) \
{ \
    CHECK_MONOID_PERMUTED_WRT_EQUAL(op_tag)(equal, var_a, var_b, var_c);\
    CHECK_MONOID_PERMUTED_WRT_EQUAL(op_tag)(equal, var_a, var_b, ass_a);\
    CHECK_MONOID_PERMUTED_WRT_EQUAL(op_tag)(equal, var_a, var_b, ass_b);\
}

#define DEFINE_MONOID_CHECK_INSTANCE_WRT(op_tag) \
template<class TypeA, class TypeB, class TypeC, class AssocA, class AssocB> \
void check_monoid_instance_wrt_##op_tag \
(const TypeA& var_a, const TypeB& var_b, const TypeC& var_c, \
 const AssocA& ass_a, const AssocB& ass_b) \
{ \
    CHECK_MONOID_PERMUTED_WRT(op_tag)(var_a, var_b, var_c);\
    CHECK_MONOID_PERMUTED_WRT(op_tag)(var_a, var_b, ass_a);\
    CHECK_MONOID_PERMUTED_WRT(op_tag)(var_a, var_b, ass_b);\
}

DEFINE_MONOID_CHECK_INSTANCE_WRT      (plus)
DEFINE_MONOID_CHECK_INSTANCE_WRT_EQUAL(plus)
DEFINE_MONOID_CHECK_INSTANCE_WRT      (pipe)
DEFINE_MONOID_CHECK_INSTANCE_WRT_EQUAL(pipe)
DEFINE_MONOID_CHECK_INSTANCE_WRT      (et)
DEFINE_MONOID_CHECK_INSTANCE_WRT_EQUAL(et)
DEFINE_MONOID_CHECK_INSTANCE_WRT      (caret)
DEFINE_MONOID_CHECK_INSTANCE_WRT_EQUAL(caret)

#define CHECK_MONOID_INSTANCE_WRT(op_tag)       check_monoid_instance_wrt_##op_tag
#define CHECK_MONOID_INSTANCE_WRT_EQUAL(op_tag) check_monoid_instance_wrt_equal_##op_tag



//------------------------------------------------------------------------------
// Abelian modoid instance
//------------------------------------------------------------------------------

#define DEFINE_ABELIAN_MONOID_CHECK_INSTANCE_WRT_EQUAL(op_tag) \
template<class TypeA, class TypeB, class TypeC, class AssocA, class AssocB> \
void check_abelian_monoid_instance_wrt_equal_##op_tag \
(typename equality<TypeA>::type* equal, const TypeA& var_a, const TypeB& var_b, const TypeC& var_c, \
 const AssocA& ass_a, const AssocB& ass_b) \
{ \
    CHECK_ABELIAN_MONOID_PERMUTED_WRT_EQUAL(op_tag)(equal, var_a, var_b, var_c);\
    CHECK_ABELIAN_MONOID_PERMUTED_WRT_EQUAL(op_tag)(equal, var_a, var_b, ass_a);\
    CHECK_ABELIAN_MONOID_PERMUTED_WRT_EQUAL(op_tag)(equal, var_a, var_b, ass_b);\
}

#define DEFINE_ABELIAN_MONOID_CHECK_INSTANCE_WRT(op_tag) \
template<class TypeA, class TypeB, class TypeC, class AssocA, class AssocB> \
void check_abelian_monoid_instance_wrt_##op_tag \
(const TypeA& var_a, const TypeB& var_b, const TypeC& var_c, \
 const AssocA& ass_a, const AssocB& ass_b) \
{ \
    CHECK_ABELIAN_MONOID_PERMUTED_WRT(op_tag)(var_a, var_b, var_c);\
    CHECK_ABELIAN_MONOID_PERMUTED_WRT(op_tag)(var_a, var_b, ass_a);\
    CHECK_ABELIAN_MONOID_PERMUTED_WRT(op_tag)(var_a, var_b, ass_b);\
}

DEFINE_ABELIAN_MONOID_CHECK_INSTANCE_WRT      (plus)
DEFINE_ABELIAN_MONOID_CHECK_INSTANCE_WRT_EQUAL(plus)
DEFINE_ABELIAN_MONOID_CHECK_INSTANCE_WRT      (pipe)
DEFINE_ABELIAN_MONOID_CHECK_INSTANCE_WRT_EQUAL(pipe)
DEFINE_ABELIAN_MONOID_CHECK_INSTANCE_WRT      (et)
DEFINE_ABELIAN_MONOID_CHECK_INSTANCE_WRT_EQUAL(et)
DEFINE_ABELIAN_MONOID_CHECK_INSTANCE_WRT      (caret)
DEFINE_ABELIAN_MONOID_CHECK_INSTANCE_WRT_EQUAL(caret)

#define CHECK_ABELIAN_MONOID_INSTANCE_WRT(op_tag)       check_abelian_monoid_instance_wrt_##op_tag
#define CHECK_ABELIAN_MONOID_INSTANCE_WRT_EQUAL(op_tag) check_abelian_monoid_instance_wrt_equal_##op_tag


//------------------------------------------------------------------------------
// Abelian partial invertive modoid instance
//------------------------------------------------------------------------------

#define DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_INSTANCE_WRT_EQUAL(op_tag) \
template<class TypeA, class TypeB, class TypeC, class AssocA, class AssocB> \
void check_partial_invertive_monoid_instance_wrt_equal_##op_tag \
(typename equality<TypeA>::type* equal, const TypeA& var_a, const TypeB& var_b, const TypeC& var_c, \
 const AssocA& ass_a, const AssocB& ass_b) \
{ \
    CHECK_PARTIAL_INVERTIVE_MONOID_PERMUTED_WRT_EQUAL(op_tag)(equal, var_a, var_b, var_c);\
    CHECK_PARTIAL_INVERTIVE_MONOID_PERMUTED_WRT_EQUAL(op_tag)(equal, var_a, var_b, ass_a);\
    CHECK_PARTIAL_INVERTIVE_MONOID_PERMUTED_WRT_EQUAL(op_tag)(equal, var_a, var_b, ass_b);\
}

#define DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_INSTANCE_WRT(op_tag) \
template<class TypeA, class TypeB, class TypeC, class AssocA, class AssocB> \
void check_partial_invertive_monoid_instance_wrt_##op_tag \
(const TypeA& var_a, const TypeB& var_b, const TypeC& var_c, \
 const AssocA& ass_a, const AssocB& ass_b) \
{ \
    CHECK_PARTIAL_INVERTIVE_MONOID_PERMUTED_WRT(op_tag)(var_a, var_b, var_c);\
    CHECK_PARTIAL_INVERTIVE_MONOID_PERMUTED_WRT(op_tag)(var_a, var_b, ass_a);\
    CHECK_PARTIAL_INVERTIVE_MONOID_PERMUTED_WRT(op_tag)(var_a, var_b, ass_b);\
}

DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_INSTANCE_WRT      (plus)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_INSTANCE_WRT_EQUAL(plus)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_INSTANCE_WRT      (pipe)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_INSTANCE_WRT_EQUAL(pipe)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_INSTANCE_WRT      (et)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_INSTANCE_WRT_EQUAL(et)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_INSTANCE_WRT      (caret)
DEFINE_PARTIAL_INVERTIVE_MONOID_CHECK_INSTANCE_WRT_EQUAL(caret)

#define CHECK_PARTIAL_INVERTIVE_MONOID_INSTANCE_WRT(op_tag)       check_partial_invertive_monoid_instance_wrt_##op_tag
#define CHECK_PARTIAL_INVERTIVE_MONOID_INSTANCE_WRT_EQUAL(op_tag) check_partial_invertive_monoid_instance_wrt_equal_##op_tag


//------------------------------------------------------------------------------
// Abelian group instance
//------------------------------------------------------------------------------

#define DEFINE_ABELIAN_GROUP_CHECK_INSTANCE_WRT_EQUAL(op_tag) \
template<class TypeA, class TypeB, class TypeC, class AssocA, class AssocB> \
    void check_abelian_group_instance_wrt_equal_##op_tag \
(typename equality<TypeA>::type* equal, const TypeA& var_a, const TypeB& var_b, const TypeC& var_c, \
 const AssocA& ass_a, const AssocB& ass_b) \
{ \
    CHECK_ABELIAN_GROUP_PERMUTED_WRT_EQUAL(op_tag)(equal, var_a, var_b, var_c);\
    CHECK_ABELIAN_GROUP_PERMUTED_WRT_EQUAL(op_tag)(equal, var_a, var_b, ass_a);\
    CHECK_ABELIAN_GROUP_PERMUTED_WRT_EQUAL(op_tag)(equal, var_a, var_b, ass_b);\
}

#define DEFINE_ABELIAN_GROUP_CHECK_INSTANCE_WRT(op_tag) \
template<class TypeA, class TypeB, class TypeC, class AssocA, class AssocB> \
    void check_abelian_group_instance_wrt_##op_tag \
(const TypeA& var_a, const TypeB& var_b, const TypeC& var_c, \
 const AssocA& ass_a, const AssocB& ass_b) \
{ \
    CHECK_ABELIAN_GROUP_PERMUTED_WRT(op_tag)(var_a, var_b, var_c);\
    CHECK_ABELIAN_GROUP_PERMUTED_WRT(op_tag)(var_a, var_b, ass_a);\
    CHECK_ABELIAN_GROUP_PERMUTED_WRT(op_tag)(var_a, var_b, ass_b);\
}

DEFINE_ABELIAN_GROUP_CHECK_INSTANCE_WRT      (plus)
DEFINE_ABELIAN_GROUP_CHECK_INSTANCE_WRT_EQUAL(plus)
DEFINE_ABELIAN_GROUP_CHECK_INSTANCE_WRT      (pipe)
DEFINE_ABELIAN_GROUP_CHECK_INSTANCE_WRT_EQUAL(pipe)

#define CHECK_ABELIAN_GROUP_INSTANCE_WRT(op_tag)       check_abelian_group_instance_wrt_##op_tag
#define CHECK_ABELIAN_GROUP_INSTANCE_WRT_EQUAL(op_tag) check_abelian_group_instance_wrt_equal_##op_tag

}} // namespace icl boost

#endif // BOOST_LIBS_ICL_TEST_ICL_LAWS_HPP_JOFA_090119

