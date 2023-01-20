import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class ComputerScienceDegree{
    private ArrayList<Student> students;

    public ComputerScienceDegree(){
        students = new ArrayList<Student>();
    }

    public void addStudent(Student s){
        students.add(s);
    }

    public void load(String filename) throws IOException{
        File file = new File(filename);
        if(!file.exists()){
            throw new IOException("File non trovato");
        }
        BufferedReader reader = new BufferedReader(new java.io.FileReader(file));
        while(reader.ready()){
            String frase = reader.readLine();
            StringTokenizer tokenizer = new StringTokenizer(frase, ",");
            while(tokenizer.hasMoreTokens()){
                ArrayList<String> spezzettato = new ArrayList<String>();
                while(tokenizer.hasMoreTokens()){
                    spezzettato.add(tokenizer.nextToken());
                }
                int matricola = Integer.parseInt(spezzettato.get(0));
                String nome = spezzettato.get(1);
                Student s = new Student(nome, matricola);
                for(int i = 2; i < spezzettato.size(); i++){
                    String nomeesame = spezzettato.get(i);
                    i++;
                    int crediti = Integer.parseInt(spezzettato.get(i));
                    i++;
                    int orale = Integer.parseInt(spezzettato.get(i));
                    i++;
                    ArrayList<Integer> scritti = new ArrayList<Integer>();
                    StringTokenizer tokenizer2 = new StringTokenizer(spezzettato.get(i), ";");
                    while(tokenizer2.hasMoreTokens()){
                        scritti.add(Integer.parseInt(tokenizer2.nextToken()));
                    }
                    if(scritti.size()==1){
                        WrittenAndOralExam esame = new WrittenAndOralExam(nomeesame, crediti);
                        esame.setOralGrade(orale);
                        esame.setWrittenGrade(scritti.get(0));
                        s.addExam(esame);
                    }else{
                        ContinuousEvaluationExam esame = new ContinuousEvaluationExam(nomeesame, crediti);
                        esame.setOralGrade(orale);
                        for(int voto : scritti){
                            esame.addContinuousEvaluationGrade(voto);
                        }
                        s.addExam(esame);
                    }

                }
                
            }
        
        }
        reader.close();
    }

    public int getYearlyStudents(int year){
        int count = 0;
        if( year < 1 || year > 3){
            throw new IllegalArgumentException("Anno non valido");
        }
        for(Student s : students){
            if(s.getYear() == year){
                count++;
            }
        }
        return count;
    }

    public Student getTopStudentPerYear(int year){
        ArrayList<Student> studentsPerYear = new ArrayList<>();
        for(Student s : students){
            if(s.getYear() == year){
                studentsPerYear.add(s);
            }
        }
        if(studentsPerYear.size() == 0){
            return null;
        }
        Student bestStudent = studentsPerYear.get(0);
        for(Student s : studentsPerYear){
            if(s.getECTSAverage() > bestStudent.getECTSAverage()){
                bestStudent = s;
            }else if(s.getECTSAverage() == bestStudent.getECTSAverage() && s.getStudentNumber() < bestStudent.getStudentNumber()){
                bestStudent = s;
            }
        }
        return bestStudent;
    }
}