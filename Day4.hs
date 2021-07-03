import Text.Parsec
import Text.Parsec.String
import Control.Monad (guard)
import Data.Maybe (mapMaybe, isJust)
import Data.List.Split hiding (sepBy, endBy, oneOf)
import qualified Data.Map as M
import Data.Map (Map)
import Data.List ((\\))
import Text.Read (readMaybe)
import Data.Char
import Data.Semigroup (All(All), getAll)

hush :: Either e a -> Maybe a
hush (Left _)  = Nothing
hush (Right a) = Just a

parse' :: Parser a -> String -> Maybe a
parse' p = hush . parse p ""

-- Part 1
parsePassport :: String -> Either ParseError (Map String String)
parsePassport = fmap M.fromList . parse' (kvp `sepEndBy` space)
  where
    kvp = (,) <$> manyTill anyChar (char ':')
              <*> many (noneOf "\n ")

hasRequiredFields :: Map String String -> Bool
hasRequiredFields m =  null $ ["byr", "ecl", "eyr", "hcl", "hgt", "iyr", "pid"] \\ M.keys m

validatePassports :: (Map String String -> Bool) -> String -> [Map String String]
validatePassports v = filter v . mapMaybe (hush . parsePassport) . splitOn "\n\n"

solveP1 :: String -> Int
solveP1 = length . validatePassports hasRequiredFields

-- Part 2
type Validation a = (a -> Maybe a)

within :: (Int, Int) -> Int -> Bool
within (min, max) i = i >= min && i <= max

year :: String -> Maybe Int
year s = parse' (4 `times` digit) s >>= readMaybe

yearBetween :: (Int, Int) -> String -> Maybe String
yearBetween r s = year s >>= \n -> guard (within r n) >> pure s

byr :: Validation String
byr = yearBetween (1929, 2020)

iyr :: Validation String
iyr = yearBetween (2010, 2020)

eyr :: Validation String
eyr = yearBetween (2020, 2030)

hgt :: Validation String
hgt = parse' (mappend <$> many1 digit <*> (try (string "cm") <|> try (string "in")))

hcl :: Validation String
hcl = parse' (mappend <$> string "#" <*> 6 `times` anyChar)

ecl :: Validation String
ecl s | s == "amb" = Just s
      | s == "blu" = Just s
      | s == "brn" = Just s
      | s == "gry" = Just s
      | s == "grn" = Just s
      | s == "hzl" = Just s
      | s == "oth" = Just s
      | otherwise  = Nothing

pid :: Validation String
pid s = guard (length s == 9 && isNumber s) >> pure s
  where isNumber = getAll . foldMap (All . isDigit)

validateFields :: Map String String -> Maybe (Map String String)
validateFields = M.traverseWithKey validateAtKey
  where
    validateAtKey = \case "byr" -> byr
                          "iyr" -> iyr
                          "eyr" -> eyr
                          "hgt" -> hgt
                          "hcl" -> hcl
                          "ecl" -> ecl
                          _     -> Just

solveP2 :: String -> Int
solveP2 = length . validatePassports (\x -> hasRequiredFields x &&
                                            isJust (validateFields x))
