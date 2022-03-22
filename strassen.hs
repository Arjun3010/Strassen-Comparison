-- Import Modules --
import Data.List
import Text.Printf
import Control.Exception
import System.CPUTime

-- Time Function to compute execution time --
time :: IO t -> IO t
time a = do
    start <- getCPUTime
    v <- a
    end   <- getCPUTime
    let diff = (fromIntegral (end - start)) / (10^12)
    printf "Computation time: %0.10f sec\n" (diff :: Double)
    return v
    
-- Obtaining Matrix --
data Matrix a = Matrix { get :: [[a]] } deriving ( Show )
 
instance ( Num a ) => Num ( Matrix a ) where
    ( Matrix xs ) + ( Matrix ys ) = Matrix ( zipWith ( \ x y -> zipWith ( + ) x y ) xs ys )
    ( Matrix xs ) - ( Matrix ys ) = Matrix ( zipWith ( \ x y -> zipWith ( - ) x y ) xs ys )
    ( Matrix xs ) * ( Matrix ys ) = Matrix ( map ( \x ->  map ( sum.zipWith (*) x  ) ( transpose  ys ) ) xs )
    abs ( Matrix xs ) = undefined
    signum ( Matrix xs ) = undefined
    fromInteger _  = undefined
 
-- Recursion Multiplication for Strassen's -- 
recurMult :: ( Num a ) => Int -> Int -> Matrix a -> Matrix a -> Matrix a
recurMult n lev xs ys
     | lev >= 2 = xs * ys -- not splitting matrix more than 2 levels 
     | otherwise =  Matrix ret where
              n' = div n 2
              ( a , b ) = ( get xs , get ys )
              ( a_u , a_l ) = splitAt n' a
              ( b_u , b_l ) = splitAt n' b
              ( a11 , a12 ) = ( Matrix { get =  map ( fst . splitAt n' ) a_u }  , Matrix { get =  map ( snd . splitAt n' ) a_u } )
              ( a21 , a22 ) = ( Matrix { get =  map ( fst . splitAt n' ) a_l }  , Matrix { get =  map ( snd . splitAt n' ) a_l } )
              ( b11 , b12 ) = ( Matrix { get =  map ( fst . splitAt n' ) b_u }  , Matrix { get =  map ( snd . splitAt n' ) b_u } )
              ( b21 , b22 ) = ( Matrix { get =  map ( fst . splitAt n' ) b_l }  , Matrix { get =  map ( snd . splitAt n' ) b_l } )
              Matrix c11 = recurMult n' ( lev + 1 ) a11  b11  +  recurMult n' ( lev + 1 ) a12  b21
              Matrix c12 = recurMult n' ( lev + 1 ) a11  b12  +  recurMult n' ( lev + 1 ) a12  b22
              Matrix c21 = recurMult n' ( lev + 1 ) a21  b11  +  recurMult n' ( lev + 1 ) a22  b21
              Matrix c22 = recurMult n' ( lev + 1 ) a21  b12  +  recurMult n' ( lev + 1 ) a22  b22
 
              ret = ( zipWith ( ++ ) c11 c12 ) ++ ( zipWith ( ++ ) c21 c22 )
 
-- Compute and Merge Strassen's --  
tempMult :: ( Num a ) =>  [ [ a ] ] -> [ [ a ] ] ->  [ [ a ] ]
tempMult xs ys = get $ recurMult ( length xs ) 0 ( Matrix xs ) ( Matrix ys )
 
-- Main Function --
main::IO()
main = do
    print ("4 x 4 matrix")
    time $ print (tempMult ([[1, 2, 3, 4 ], [1, 2, 3, 4], [1, 2, 3, 4], [1, 2, 3, 4]]) ([[1, 2, 3, 4], [1, 2, 3, 4], [1, 2, 3, 4], [1, 2, 3, 4]]))
    print ("6 x 6 matrix")
    time $ print (tempMult ([[2, 0, 4, 4, 9, 0], [7, 8, 3, 4, 4, 7], [9, 8, 8, 0, 4, 4], [1, 2, 7, 6, 2, 0], [5, 2, 7, 5, 6, 8], [3, 5, 8, 1,7, 4]]) ([[5, 2, 5, 4, 0, 7], [1, 1, 3, 6, 3, 4], [8, 7, 2, 3, 7, 3], [3, 8, 7, 0, 0, 5], [3, 4, 8, 3, 4, 1], [6, 1, 6, 4, 8, 0]]))
    print ("8 x 8 matrix")
    time $ print (tempMult ([[4, 3, 4, 7, 3, 5, 7, 7], [5, 5, 5, 7, 6, 4, 6, 3], [6, 0, 5, 5, 3, 8, 7, 9], [8, 7, 4, 0, 5, 0, 0, 9], [7, 7, 9, 9, 9, 0, 3, 6], [5, 5, 4, 1, 6, 7, 1, 6], [4, 0, 5, 0, 3, 0, 1, 7], [9, 3, 7, 3, 9, 0, 0, 2]]) ([[9, 2, 3, 0, 0, 6, 7, 1], [2, 9, 7, 6, 6, 5, 3, 3], [4, 9, 7, 5, 6, 3, 8, 7], [6, 9, 4, 4, 2, 2, 7, 3], [5, 0, 5, 6, 9, 4, 1, 5], [3, 1, 1, 0, 5, 1, 3, 8], [3, 8, 3, 2, 3, 9, 2, 9], [1, 5, 0, 0, 1, 9, 2, 5]]))
