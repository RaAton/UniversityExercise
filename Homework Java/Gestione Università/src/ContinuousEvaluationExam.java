import java.util.ArrayList;

public class ContinuousEvaluationExam extends AbstractExam {
    public ArrayList<Integer> continuousEvaluationGrades;

    public ContinuousEvaluationExam(String examName, int credits) {
        super(examName, credits);
        continuousEvaluationGrades = new ArrayList<>();
    }

    public void addContinuousEvaluationGrade(int g) {
        if (g < 0 || g > 30) {
            throw new IllegalArgumentException("Invalid grade. Must be between 0 and 30.");
        }
        continuousEvaluationGrades.add(g);
    }

    @Override
    public int getGrade() {
        int totale = 0;
        for (int voto : continuousEvaluationGrades) {
            totale += voto;
        }
        int itinere = Math.round(totale / continuousEvaluationGrades.size());
        return Math.round((itinere + this.getOralGrade()) / 2);
    }
}
