package fact.it.mvc.manageExSQ;

import javax.persistence.Entity;
import javax.persistence.Table;

import fact.it.mvc.ExSQList.ExerciseSequenceList;

import javax.persistence.Id;
import javax.persistence.OneToMany;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Column;
import javax.persistence.CascadeType;
import lombok.Data;
import java.util.List;

@Entity
@Data
@Table(name = "ExerciseSequence")
public class ExerciseSequence {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "exSQID")
    private int exSQID;

    @Column(name = "name")
    private String name;

    @Column(name = "description")
    private String description;

    @OneToMany(mappedBy = "exSQID", cascade = CascadeType.ALL)
    private List<ExerciseSequenceList> exerciseSequenceLists;

    // Getter method for sequenceId
    public int getSequenceId() {
        return exSQID;
    }
}
