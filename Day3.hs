trees right down xs = let line_length = length (head xs)
                      in length $ filter (== '#') $ 
                            zipWith (\input move -> input !! (move `mod` line_length))
                                    (downs down xs) [right,right+right..]
    where
        downs d xs = let ys = drop d xs in if null ys then [] else head ys : downs d ys

main = do xs <- readFile "day3_input" <&> lines
          let task1 = trees 3 1 xs
          let task2 = [  trees 1 1 xs, trees 3 1 xs,  trees 5 1 xs, 
                         trees 7 1 xs, trees 1 2 xs ]
          print task1 >> print (product task2)
