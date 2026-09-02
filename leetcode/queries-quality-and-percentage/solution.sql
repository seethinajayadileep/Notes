# Write your MySQL query statement below
select query_name,ROUND(sum(q.rating/q.position)/count(*),2)as quality  ,
ROUND(AVG(CASE WHEN rating <3 Then 100.0 else 0 end),2) as poor_query_percentage from queries q 
where query_name is not null
group by query_name
