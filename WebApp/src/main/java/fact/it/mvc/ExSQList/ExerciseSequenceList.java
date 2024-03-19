package fact.it.mvc.ExSQList;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Table;

import javax.persistence.Id;
import javax.persistence.Column;

import lombok.Data;

@Entity
@Data
@Table(name = "ExerciseSequenceList")
public class ExerciseSequenceList {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "exSQListID")
    private int exSQListID;
    
    @Column(name = "exID")
    private int exID;
    
    @Column(name = "exSQID")
    private int exSQID;

    @Column(name = "place")
    private int place;
}