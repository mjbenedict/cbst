def highest_bit_set a
val = 0
while a
  bit = 1<<val
  puts  "a is #{a} bit #{bit} val #{val}"
  a &= ~bit
  return val if 0 == a
  val += 1
  end
end

def treeify array
  count = array.length
  out = []
  span = 1<<highest_bit_set(count)
  index = 1

  for i in 0..array.length
    out[i] = nil
  end
  while span > 0
    iter = 1
    while (span*iter-1) < count
      puts "puting out [#{index}] = #{out[index]} at BST[#{span*(iter)}-1] with span #{span} iter #{iter} <<#{count}>>"
#      out [index] = buf [iter*span]
      out[index] = array [span*iter-1]
      puts "out #{out}"
      puts "array #{array}"
      iter += 2
      index += 1
      return out if count > 40
    end
    span /= 2
  end

  out
end

  

def order buf
  count = buf.length-1
  out = []
  span = 1<<highest_bit_set(count)
  index = 1

  for i in 0..(count-1)
    out[i] = nil
  end
  while span > 0
    iter = 1
#    puts "#{span+span*iter} < #{count}"
    while (span*iter-1) < count
      puts "puting BST [#{index}] = #{buf[index]} at out[#{span*(iter)}-1] with span #{span} iter #{iter} <<#{count}>>"
#      out [index] = buf [iter*span]
      out [span*iter-1] = buf[index]

      puts "out #{out}"
      puts "buf #{buf}"
      iter += 2
      index += 1
      return out if count > 40
    end
    span /= 2
  end

  out
end


def print_in_order_internal (buf,start,count)
  if print < count
    print_in_order buf, start*2, count
    puts buf[start]
    print_in_order buf,start*2+1, count
  end
end

def print_in_order buf
  print_in_order_internal buf, 1, buf.length
end

def iter_print_in_order buf
  index = buf.length
  first = highest_bit_set count

  puts buf[index]

  while index > 1
    puts buf[index/2]
    puts buf[index+1] unless index >= count
  end
# fuckit
end
