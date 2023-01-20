public abstract class AbstractExam implements IExam {
    private int credits;
    private String examName;
    private int oralGrade;

    public AbstractExam(String examName, int credits) {
        this.examName = examName;
        this.credits = credits;
    }

    public int getOralGrade() {
        return oralGrade;
    }

    public void setOralGrade(int oralGrade) {
        if (oralGrade < 0 || oralGrade > 30) {
            throw new IllegalArgumentException("Il voto deve essere tra 0 e 30");
        }
        this.oralGrade = oralGrade;
    }

    public String getExamName() {
        return examName;
    }

    public int getCredits() {
        return credits;
    }

}