#include <bits/stdc++.h>

using namespace std;

struct Movie {
    string title;
    double imdbRating;
    int releaseYear;
    int watchTimePopularity;
};

void printMovies(const vector<Movie>& movies, const string& title) {
    cout << "--- " << title << " ---" << endl;
    for (const auto& movie : movies) {
        cout << "  [" << movie.title << "] "
             << "(Rating: " << fixed << setprecision(1) << movie.imdbRating << ", "
             << "Year: " << movie.releaseYear << ", "
             << "Pop: " << movie.watchTimePopularity << ")" << endl;
    }
    cout << "---------------------------------" << endl << endl;
}

int main() {
    int n;
    cout << "Enter the number of movies: ";
    cin >> n;

    // Clear the newline character left in the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    vector<Movie> movies;
    for (int i = 0; i < n; ++i) {
        Movie tempMovie;
        
        cout << "Enter movie " << i + 1 << " title: ";
        getline(cin, tempMovie.title);
        
        cout << "Enter movie " << i + 1 << " rating: ";
        cin >> tempMovie.imdbRating;
        
        cout << "Enter movie " << i + 1 << " year: ";
        cin >> tempMovie.releaseYear;
        
        cout << "Enter movie " << i + 1 << " popularity: ";
        cin >> tempMovie.watchTimePopularity;

        // Clear the buffer again for the next call to getline()
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        
        movies.push_back(tempMovie);
        cout << endl; // Add a space between movie entries
    }

    printMovies(movies, "Original Movie List");

    // Make one copy to perform all sorting operations on
    vector<Movie> sortedMovies = movies;

    // Case 1: Sort by IMDB Rating (Descending)
    sort(sortedMovies.begin(), sortedMovies.end(),
        [](const Movie& a, const Movie& b) {
            return a.imdbRating > b.imdbRating;
        }
    );
    printMovies(sortedMovies, "Sorted by IMDB Rating (Descending)");


    // Case 2: Sort by Release Year (Newest First)
    sort(sortedMovies.begin(), sortedMovies.end(),
        [](const Movie& a, const Movie& b) {
            return a.releaseYear > b.releaseYear;
        }
    );
    printMovies(sortedMovies, "Sorted by Release Year (Newest First)");


    // Case 3: Sort by Watch Time Popularity (Most Popular First)
    sort(sortedMovies.begin(), sortedMovies.end(),
        [](const Movie& a, const Movie& b) {
            return a.watchTimePopularity > b.watchTimePopularity;
        }
    );
    printMovies(sortedMovies, "Sorted by Popularity (Descending)");


    // Case 4: Sort by Title (Alphabetical A-Z)
    sort(sortedMovies.begin(), sortedMovies.end(),
        [](const Movie& a, const Movie& b) {
            return a.title < b.title;
        }
    );
    printMovies(sortedMovies, "Sorted by Title (Alphabetical)");

    return 0;
}