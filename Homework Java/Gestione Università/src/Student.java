import java.util.ArrayList;

public class Student implements java.lang.Comparable<Student> {
    private String name;
    private int studentNumber;
    private ArrayList<AbstractExam> exams;
    
    public Student(String name, int studentNumber) {
        this.name = name;
        this.studentNumber = studentNumber;
        this.exams = new ArrayList<AbstractExam>();
    }
    
    public String getName() {
        return name;
    }
    
    public int getStudentNumber() {
        return studentNumber;
    }
    
    public void addExam(AbstractExam exam) {
        for (AbstractExam e : exams) {
            if (e.getExamName().equals(exam.getExamName())) {
                exams.remove(e);
                break;
            }
        }
        exams.add(exam);
    }
    
    public int getYear() {
        int cfu = 0;
        for (AbstractExam e : exams) {
            if (e.getGrade() > 17) {
                cfu += e.getCredits();
            }
        }
        if (cfu < 60) {
            return 1;
        } else if (cfu < 120) {
            return 2;
        } else {
            return 3;
        }
    }

    public double getECTSAverage(){
        double cfu = 0.0;
        double media = 0.0;
        if(exams.isEmpty())
            return 0.0;
        for (AbstractExam e : exams) {
            if (e.getGrade() > 17) {
                cfu += (double)e.getCredits();
                media += (double)e.getGrade() * (double)e.getCredits();
            }
        }
        return media / cfu;
    }

    @Override
    public int compareTo(Student s) {
        int ordine;
        if (this.getECTSAverage() > s.getECTSAverage()) {
            ordine = 1;
        } else if (this.getECTSAverage() < s.getECTSAverage()) {
            ordine = -1;
        } else {
            ordine = 0;
        }
        return ordine;
    }
    
}
