package fact.it.mvc.UserExerciseSequence;
import java.io.Serializable;

public class UserExcerciseSequenceId implements Serializable {
    private int userID;
    private int exSQID;
    
    // Constructors
    public UserExcerciseSequenceId() {
        // Default constructor
    }
    
    public UserExcerciseSequenceId(int userID, int exSQID) {
        this.userID = userID;
        this.exSQID = exSQID;
    }
    
    // Getters and Setters
    public int getUserID() {
        return userID;
    }

    public void setUserID(int userID) {
        this.userID = userID;
    }

    public int getExSQID() {
        return exSQID;
    }

    public void setExSQID(int exSQID) {
        this.exSQID = exSQID;
    }

    // Equals method override
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        UserExcerciseSequenceId that = (UserExcerciseSequenceId) o;
        return userID == that.userID &&
                exSQID == that.exSQID;
    }
}