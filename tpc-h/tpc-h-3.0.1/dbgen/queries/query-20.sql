-- using 1708546893 as a seed to the RNG


select
	s_name,
	s_address
from
	supplier,
	nation
where
	s_suppkey in (
		select
			ps_suppkey
		from
			partsupp
		where
			ps_partkey in (
				select
					p_partkey
				from
					part
				where
					p_name like 'maroon%'
			)
			and ps_availqty > (
				select
					0.5 * sum(l_quantity)
				from
					lineitem
				where
					l_partkey = ps_partkey
					and l_suppkey = ps_suppkey
					and l_shipdate >= date '1997-01-01'
					and l_shipdate < date '1997-01-01' + interval '1' year
			)
	)
	and s_nationkey = n_nationkey
	and n_name = 'ETHIOPIA'
order by
	s_name;
set rowcount -1
go

