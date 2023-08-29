# tideman-election
Welcome to the CS50 Problem Set Solutions repository! Here, you'll find my solution for one of the problem sets from Harvard's renowned CS50 Introduction to Computer Science course. This problem set involves creating an algorithm that ranks candidates participating in a tideman election. 

## Description

A tideman election is a ranked-choice voting system, which voters can vote in more than one candidate. This system solves the disadvantages of the plurality election system, which does not resolve a tied election. In the tideman election produces a locked graph, where you determine the relation between candidates in a head-to-head matchup, so if one candidate is prefered over another an arrow will be drawn towards the loser. The winner of the election is the source of the graph, so the one that has no arrows pointing at them. 

On this problem I have completed: 

- [vote] function, which I check if the voter voted to a valid candidate and if the rank is successufully recorded returns true. 
- [record_preferences] function which updates the global preferences array to add the current voter's preferences
- [add_pairs] function which add all candidates pairs and checked when the candidates are tied, in which should not be added to the array
- [sort_pairs] function which sort the pairs array using bubble sort
- [lock_pairs] function which creates a locked graph, adding all edges as long as would not create a cycle
- [print_winner] function which prints the winner 

## Contribution Guidelines

The contribution guidelines are as per the guide HERE(https://github.com/tsdamas/tideman-election/blob/main/CONTRIBUTIONS).

Instructions Fork this Repository Clone your forked repository Add your scripts Commit & Push Create a pull request Star this repository Wait for Pull Request to merge Celebrate, your first step into the open Source World and contribute more

Note: When you Add a project Add it to the README for ease of finding it Note: Please do not put the project link to reference your local forked repo. Always link it to this repo after it's been merged with main.

## Requirements

This module requires no modules outside of the branch. 

## License

[MIT License](https://choosealicense.com/licenses/mit/)

## Built with 

- C

## Links

- [Repo](https://github.com/tsdamas/tideman-election "<tideman-election> Repo")

- [Bugs](https://github.com/tsdamas/tideman-election/issues "Issues Page")

## Future Updates

- [ ] Front-end 


## Author

**Thais Damasceno**

- [Profile](https://github.com/tsdamas "Thais Damasceno")
- [Email](mailto:tssdamasceno@gmail.com?subject=Hi "Hi!")
- [Website](https://stoic-mclean-831fce.netlify.app "Welcome")

## 🤝 Support

Contributions, issues, and feature requests are welcome!
