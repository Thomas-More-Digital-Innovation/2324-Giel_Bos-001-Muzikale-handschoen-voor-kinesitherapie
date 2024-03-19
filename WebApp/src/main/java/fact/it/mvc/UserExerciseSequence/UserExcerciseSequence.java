package fact.it.mvc.UserExerciseSequence;


import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Id;
import javax.persistence.Column;
import lombok.Data;
import javax.persistence.IdClass;

@Entity
@Data
@Table(name = "UserExcerciseSequence")
@IdClass(UserExcerciseSequenceId.class)
public class UserExcerciseSequence {
    @Id
    @Column(name = "userID")
    private int userID;
    
    @Id
    @Column(name = "exSQID")
    private int exSQID;
}
