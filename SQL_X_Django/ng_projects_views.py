from django.shortcuts import render
from django.http import Http404

from projects.models import Project, Category, Photo, Embedded, Code, File, Link
from skills.models import Skill

def projects(request, project_id=1):
    try:
        project = Project.objects.get(id=project_id)
    except Project.DoesNotExist:
        raise Http404('project not found')

    # note the categories_that_have_prj_not_mini would still maps to set of prj that has mini_project
    # it is excluded in template
    categories_that_have_prj_not_mini = Category.objects.filter(project__isnull=False, project__is_mini=False).distinct()
    categories =  project.categories.all()
    used_skills = project.used_skills.all()

    embeddeds = Embedded.objects.filter(project_id=project_id)
    photos = Photo.objects.filter(project_id=project_id)
    links = Link.objects.filter(project_id=project_id)
    codes = Code.objects.filter(project_id=project_id)
    files = File.objects.filter(project_id=project_id)

    return render(request, 'projects.html', {
        'categories_that_have_prj_not_mini':categories_that_have_prj_not_mini,
        'project':project,
        'categories':categories,
        'used_skills':used_skills,
        'embeddeds':embeddeds,
        'photos':photos,
        'links':links,
        'codes':codes,
        'files':files,
    })
