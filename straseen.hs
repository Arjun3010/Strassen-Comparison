import Data.List


data Matrix a = Matrix { get :: [[a]] } deriving ( Show )

instance ( Num a ) => Num ( Matrix a ) where
    ( Matrix xs ) + ( Matrix ys ) = Matrix ( zipWith ( \ x y -> zipWith ( + ) x y ) xs ys )
    ( Matrix xs ) - ( Matrix ys ) = Matrix ( zipWith ( \ x y -> zipWith ( - ) x y ) xs ys )
    ( Matrix xs ) * ( Matrix ys ) = Matrix ( map ( \x ->  map ( sum.zipWith (*) x  ) ( transpose  ys ) ) xs )
    abs ( Matrix xs ) = undefined
    signum ( Matrix xs ) = undefined
    fromInteger _  = undefined


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


tempMult :: ( Num a ) =>  [ [ a ] ] -> [ [ a ] ] ->  [ [ a ] ]

main = tempMult ( [  [ 1 , 2 , 3 , 4 ] , [ 1 , 2 , 3 , 4 ] , [ 1 , 2 , 3 , 4 ] , [ 1 , 2 , 3 , 4 ] ] )  ( [  [ 1 , 2 , 3 , 4 ] , [ 1 , 2 , 3 , 4 ] , [ 1 , 2 , 3 , 4 ] , [ 1 , 2 , 3 , 4 ] ] )
