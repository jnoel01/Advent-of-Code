all_seats = [int(
    (l.replace('B','1').replace('F','0')
    .replace('R','1').replace('L','0'))
    ,2) for l in open('input.txt')]

print(f"Part 1: Highest seat is {max(all_seats)}")

your_seat = [s for s in range(min(all_seats), max(all_seats)) 
            if s not in all_seats][0]
print(f"Part 2: Your seat is {your_seat}")
