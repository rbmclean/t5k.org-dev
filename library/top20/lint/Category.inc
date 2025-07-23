<?php

namespace Top20;

const ARCHIVABLE_COUNT = 20;
const ARCHIVABLE_CLASS_COUNT = 5;

enum Category: int
{
    case Twin = 1;
    case SophieGermain = 2;
    case Mersenne = 4;
    case Primorial = 5;
    case Cullen = 6;
    case Woodall = 7;
    case FermatDivisor = 8;
    case GF6 = 9;
    case GF10 = 10;
    case GF12 = 11;
    case GeneralizedFermat = 12;
    case APConsecutive = 13;
    case ArithmeticProgression = 14;
    case NearRepdigit = 15;
    case GeneralizedRepunit = 16;
    case GFDivisor = 18;
    case CunninghamChain = 19;
    case CunninghamChain2 = 20;
    case LucasAuriPrim = 21;
    case GeneralizedLucas = 23;//TODO skipped for discussion
    case LucasPrimitive = 24;
    case EulerIrregular = 25;
    case Irregular = 26;
    case ECPP = 27;
    case GF3 = 28;
    case GF5 = 29;
    case Factorial = 30;
    case SophieGermain2 = 31; //not linted, will be removed once the PHP implementation handles all linting
    case DividesPhi = 37;
    case Fibonacci = 39;
    case FibonacciPrimPart = 40;
    case GaussianMersenne = 41;
    case GeneralizedCullen = 42;
    case GeneralizedLucasPrim = 43;//TODO skipped for discussion
    case GeneralizedUnique = 44;
    case GeneralizedWoodall = 45;
    case Lehmer = 47;
    case Lucas = 48;
    case MersenneCofactor = 49;
    case Palindrome = 53;
    case Partitions = 54;
    case Quadruplet = 55;
    case Quintuplet = 56;
    case Repunit = 57;
    case Triplet = 61;
    case Unique = 62;
    case FibonacciCofactor = 64;
    case LucasCofactor = 65;
    case Wagstaff = 67;
    case LehmerPrimitive = 68;
    case Sextuplet = 70;
    case Septuplet = 71;

    case Largest = 3; //weird case; shouldn't be on any tags
    case LeastnPlus = 17; //unused - doubtful it will ever be used. Delete? TODO
    case NSW = 22;//TODO what is this?
    case SpecialCases = 32; //TODO can we complete get rid of this?
    case ARPT_CL = 33; //Old - can remove? TODO
    case Binomial = 34; //TODO why is this tolerated?
    case Compositorial = 35; //TODO why is this tolerated?
    case Cyclotomy = 36;//TODO why is this tolerated?
    case Elliptic = 38;//TODO deprecated - remove?
    case Illegal = 46;//TODO...
    case MillsPrime = 50;//TODO
    case Multifactorial = 51;//TODO
    case nCarmichaelFactor = 52;//TODO
    case Strobogrammatic = 58;//TODO
    case Tetradic = 59;
    case Triadic = 60;
    case GapPrimes = 63;
    case Proth = 66; //TODO why isn't this a category?
    case ktuplet = 69; //not used, but I want something like this TODO
}
