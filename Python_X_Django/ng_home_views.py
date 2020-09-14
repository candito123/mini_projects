from django.shortcuts import render
from django.http import HttpResponse

from projects.models import Project, Category
from skills.models import Skill
from django.db.models import Count

from pylab import rcParams as rcP
import matplotlib.pyplot as plt
import numpy as np
import io, urllib, base64


def home(request):
    return render(request, 'home.html')

tot_num_prjs = Project.objects.filter(is_mini=False).count()
tot_num_skis = Skill.objects.count()

def stats(request):

    cate_table_name_and_num_prj= list(
        Category.objects.filter(project__is_mini=False).annotate(num_prjs=Count('project')).values_list('name', 'num_prjs')
    )
    cate_table_name_and_num_ski= list(
        Category.objects.filter(skill__isnull=False).annotate(num_prjs=Count('project')).values_list('name', 'num_prjs')
    )
    prj_wedge_sizes=[row[1] for row in cate_table_name_and_num_prj]
    ski_wedge_sizes=[row[1] for row in cate_table_name_and_num_ski]

    def do_pct(pct, allvalues):
        absolute = int(pct / 100.*np.sum(allvalues))
        return "{:.1f}%".format(pct, absolute)

    rcP['text.color'] = 'w'
    rcP['font.size'] = '8'
    fig_ski=plt.figure()
    plt.pie(
        x=ski_wedge_sizes,
        autopct=lambda pct: do_pct(pct, ski_wedge_sizes),
        labels=[row[0] for row in cate_table_name_and_num_ski],
        )
    buf_ski = io.BytesIO()
    fig_ski.savefig(buf_ski, format = 'png', transparent=True)
    buf_ski.seek(0)
    string_ski = base64.b64encode(buf_ski.read())
    uri_ski = urllib.parse.quote(string_ski)

    fig_prj=plt.figure()
    plt.pie(
        x=prj_wedge_sizes,
        autopct=lambda pct: do_pct(pct, prj_wedge_sizes),
        labels=[row[0] for row in cate_table_name_and_num_prj],
        )
    buf_prj = io.BytesIO()
    fig_prj.savefig(buf_prj, format = 'png', transparent=True)
    buf_prj.seek(0)
    string_prj = base64.b64encode(buf_prj.read())
    uri_prj = urllib.parse.quote(string_prj)

    return render(request, 'stats.html', {
        'tot_num_prjs':tot_num_prjs,
        'tot_num_skis':tot_num_skis,
        'uri_ski':uri_ski,
        'uri_prj':uri_prj,
    })

def projects_by_date(request):
    sorted_prjs = Project.objects.filter(is_mini=False).order_by('date')
    sorted_mini_prjs = Project.objects.filter(is_mini=True).order_by('date')

    return render(request, 'projects_by_date.html', {
        'tot_num_prjs':tot_num_prjs,
        'sorted_prjs': sorted_prjs,
        'sorted_mini_prjs':sorted_mini_prjs,
    })
