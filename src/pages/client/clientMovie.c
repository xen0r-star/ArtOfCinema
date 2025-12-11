#include "clientMovie.h"

static int pageIndex = 0;
static char filterTitle[100] = "";
static char filterDate[100] = "";
static int showSort = 0;

static void prevPage() {
    if (pageIndex > 0) {
        pageIndex--;
        setCurrentPage(PAGE_CLIENT_MOVIE);
    }
}

static void nextPage() {
    pageIndex++;
    setCurrentPage(PAGE_CLIENT_MOVIE);
}

static void onSearch() {
    Input *input = getInput(0);
    if (input) {
        strcpy(filterTitle, input->value);
        strcpy(filterDate, "");
        pageIndex = 0;
        setCurrentPage(PAGE_CLIENT_MOVIE);
    }
}

static void onSort() {
    Input *input = getInput(0);
    if (input) {
        strcpy(filterDate, input->value);
        strcpy(filterTitle, "");
        pageIndex = 0;
        showSort = 0;
        setCurrentPage(PAGE_CLIENT_MOVIE);
    }
}

static void changeDisplaySort() {
    showSort = !showSort;
    setCurrentPage(PAGE_CLIENT_MOVIE);
}



void showClientMoviePage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    if (rows > 40) drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);

    drawFooter();
    buttonSetting();
    buttonBack(PAGE_CLIENT);


    int listStartY = 8;
    if (rows > 40) listStartY = 14;

    int itemHeight = 2;
    int maxItems = (rows - 6 - listStartY) / itemHeight;
    if (maxItems < 1) maxItems = 1;



    int startLine = (columns - (INPUT_WIDTH + 16 + 10 + 4)) / 2;
    if (showSort) {
        createInput(startLine, listStartY - 4, _T("client.date"), _T("client.date.format"));
        createButton(startLine + INPUT_WIDTH + 2, listStartY - 4, 16, _T("search"), PRIMARY_COLOR, STYLE_DEFAULT, onSort);
        createButton(startLine + INPUT_WIDTH + 2 + 16 + 2, listStartY - 4, 10, _T("close"), WARNING_COLOR, STYLE_DEFAULT, changeDisplaySort);
        return;
    }

    createInput(startLine, listStartY - 4, _T("client.sch.flm"), _T("client.sch.plh2"));
    createButton(startLine + INPUT_WIDTH + 2, listStartY - 4, 16, _T("search"), PRIMARY_COLOR, STYLE_DEFAULT, onSearch);
    createButton(startLine + INPUT_WIDTH + 2 + 16 + 2, listStartY - 4, 10, _T("client.date.UPPERCASE"), TERTIARY_COLOR, STYLE_DEFAULT, changeDisplaySort);


    ProjectionNode *node = getProjectionList();
    
    int matchesCount = 0;
    int displayedCount = 0;
    int skipCount = pageIndex * maxItems;
    int hasMore = 0;

    while (node != NULL) {
        Movie *movie = getMovieById(node->projection.movie_id);
        
        int match = 0;
        if (movie) {
            if (strlen(filterDate) > 0) {
                if (strstr(node->projection.datetime, filterDate) != NULL) match = 1;
            } else if (searchMovieByName(movie->name, filterTitle)) {
                match = 1;
            }
        }

        if (match) {
            if (matchesCount >= skipCount) {
                if (displayedCount < maxItems) {
                    
                    createText(startLine, 
                        listStartY + (displayedCount * itemHeight), 
                        movie->name, TERTIARY_COLOR
                    );
                    createText(
                        startLine + INPUT_WIDTH + 1, 
                        listStartY + (displayedCount * itemHeight), 
                        node->projection.datetime, TEXT_COLOR
                    );
                    
                    char str[16];
                    if (node->projection.available_seats == 0) {
                        strcpy(str, _T("full"));
                        createText(
                            startLine + INPUT_WIDTH + 2 + 16 + 1, 
                            listStartY + (displayedCount * itemHeight), 
                            str, WARNING_COLOR
                        );
                    } else {
                        snprintf(str, sizeof(str), _T("seats"), node->projection.available_seats);
                        createText(
                            startLine + INPUT_WIDTH + 2 + 16 + 1, 
                            listStartY + (displayedCount * itemHeight), 
                            str, SUCCESS_COLOR
                        );
                    }
                    
                    displayedCount++;

                } else {
                    hasMore = 1;
                    break;
                }
            }
            matchesCount++;
        }
        node = node->next;
    }


    int startBtnX = (columns - (15 + 2 + 15)) / 2;

    if (pageIndex > 0) createButton(startBtnX, rows - 5, 15, _T("prev"), PRIMARY_COLOR, STYLE_DEFAULT, prevPage);
    else               createButton(startBtnX, rows - 5, 15, _T("prev"), TEXTSECONDARY_COLOR, STYLE_DEFAULT, NULL);
    
    if (hasMore) createButton(startBtnX + 15 + 2, rows - 5, 15, _T("next"), PRIMARY_COLOR, STYLE_DEFAULT, nextPage);
    else         createButton(startBtnX + 15 + 2, rows - 5, 15, _T("next"), TEXTSECONDARY_COLOR, STYLE_DEFAULT, NULL);
}