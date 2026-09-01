# Write your MySQL query statement below

select students.student_id,students.student_name,subjects.subject_name,count(examinations.subject_name) as attended_exams from Students join Subjects left join examinations on students.student_id = examinations.student_id and subjects.subject_name=examinations.subject_name group  by 1,2,3 order by 1 asc ,3 asc  ;