# DS-Search-Engine
Final Semester Project

On a partner team, created a search engine that parses through a law corpus of 35,000+ documents. 
The engine's main features include document parser/processor, query processor, search processor, and ranking processor.

The user enters a search query, and any documents that satisfy that query are returned to the user ordered by relevance.
We implemented functionality to handle simple prefix Boolean queries entered by the user such as AND, OR, NOT and ranked results by term frequency – inverse document frequency (td-idf).

Custom implementation of:
AVL Tree, HashTable (with collisions handled by separate chaining), an inverted file index.
The inverted file index relates each unique word from the corpus to the document(s) in which it appears and allows for efficient execution of a query to quickly determine in which documents a particular query term appears.
