import java.util.ArrayList;

public class ContinuousEvaluationExam extends AbstractExam {
    private ArrayList<Integer> continuousEvaluationGrades;

    public ContinuousEvaluationExam(String examName, int credits) {
        super(examName, credits);
        continuousEvaluationGrades = new ArrayList<Integer>();
    }

    public void addContinuousEvaluationGrade(int g) {
        if (g < 0 || g > 30) {
            throw new IllegalArgumentException("Il voto deve essere tra 0 e 30");
        }else{
        continuousEvaluationGrades.add(g);
        }
    }

    @Override
    public int getGrade() {
        int totale = 0;
        for (int voto : continuousEvaluationGrades) {
            totale += voto;
        }
        int itinere = Math.round(totale / continuousEvaluationGrades.size());
        return Math.round((itinere + getOralGrade()) / 2);
    }
}
