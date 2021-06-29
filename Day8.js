function accumulatorp1()
{
  let input = document.querySelector('pre').innerHTML.trim();

  let instructions = input.split('\n');

  let sum = 0;

  for(let ii = 0; ii < instructions.length; ii++)
  {
    let [ins, val] = instructions[ii].split(' ');
    if(ins == '')
    {
      break;
    }
    switch(ins)
    {
      case 'acc':
        sum += parseInt(val, 10);        
        break;
      case 'jmp':
        ii += (parseInt(val, 10)-1);
        break;
    }

    instructions[ii] = '';
  }

  return sum;
}

function accumulatorp2()
{
  let input = document.querySelector('pre').innerHTML.trim();

  let instructions = input.split('\n');

  let sum = 0;

  for(let wrong = 0; wrong < instructions.length; wrong++)
  {
    let fail = false;
    let [wins, wval] = instructions[wrong].split(' ');
    let inscpy = instructions.slice();
    sum = 0;
    if(wins == 'nop')
    {
      inscpy[wrong] = 'jmp ' + wval;
    }
    else if(wins == 'jmp')
    {
      inscpy[wrong] = 'nop ' + wval;
    }

    for(let ii = 0; ii < inscpy.length; ii++)
    {
        let [ins, val] = inscpy[ii].split(' ');
        if(ins == '')
        {
        fail = true;
        break;
        }
        switch(ins)
        {
        case 'acc':
            sum += parseInt(val, 10);        
            break;
        case 'jmp':
            ii += (parseInt(val, 10)-1);
            break;
        }

        inscpy[ii] = '';
    }
    if(!fail)
    {
      break;
    }
  }

  return sum;
}
